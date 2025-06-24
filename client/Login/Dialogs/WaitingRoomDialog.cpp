#include "WaitingRoomDialog.h"

#include <QHBoxLayout>
#include <QMessageBox>
#include <QMetaObject>
#include <QPushButton>
#include <QVBoxLayout>
#include <QApplication>
#include <QTimer>
#include <algorithm>
#include <atomic>
#include <chrono>
#include <set>
#include <thread>

#include "Login/Mappers/SkinTraslator.h"
#include "Login/Mappers/TeamMapper.h"
#include "Login/Audio/MusicManager.h"
#include "GameClient.h"

using namespace Client;

WaitingRoomDialog::WaitingRoomDialog(const QString& playerName,
                                     const QString& teamStr,
                                     const QString& skinStr,
                                     Protocol& protocol,
                                     ServerMenu* menu,
                                     QWidget* parent)
        : QDialog(parent),
        playerName(playerName),
        teamStr(teamStr),
        skinStr(skinStr),
        protocol(protocol),
        menu(menu),
        shouldStop(false),
        isReady(false),
        gameStarted(false) {

    setWindowTitle("⌛ Waiting Room");
    resize(500, 400);
    setModal(true);

    setupUI();
    startPolling();

    if (menu) {
        menu->hide();
        menu->getMusicManager()->setVolume(0.0f);
    }
}

WaitingRoomDialog::~WaitingRoomDialog() {
    stopPolling();
}

void WaitingRoomDialog::setupUI() {
    setStyleSheet(R"(
        QWidget {
            background-color: #121212;
            color: #f0f0f0;
            font-family: 'Segoe UI', sans-serif;
            font-size: 14px;
        }
        QLabel {
            padding: 6px;
            border-radius: 4px;
        }
        QPushButton {
            background-color: #1e88e5;
            color: white;
            border-radius: 6px;
            padding: 10px 16px;
            margin: 5px;
            font-weight: bold;
        }
        QPushButton:hover {
            background-color: #1565c0;
        }
        QPushButton:disabled {
            background-color: #555555;
            color: #aaaaaa;
        }
        QScrollArea {
            border: 1px solid #333;
            border-radius: 4px;
            background-color: #1a1a1a;
        }
    )");

    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(20, 20, 20, 20);
    mainLayout->setSpacing(15);

    QLabel* title = new QLabel("🎮 Players in the Room");
    title->setStyleSheet("font-weight: bold; font-size: 18px; color: #64B5F6; padding: 10px;");
    title->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(title);

    setupPlayersArea();
    mainLayout->addWidget(playersScrollArea);

    setupButtons();
    mainLayout->addLayout(buttonLayout);

    updateSelfPlayerDisplay();
}

void WaitingRoomDialog::setupPlayersArea() {
    playersScrollArea = new QScrollArea();
    playersWidget = new QWidget();
    playersLayout = new QVBoxLayout();

    playersLayout->setSpacing(8);
    playersLayout->setContentsMargins(10, 10, 10, 10);

    playersWidget->setLayout(playersLayout);
    playersScrollArea->setWidget(playersWidget);
    playersScrollArea->setWidgetResizable(true);
    playersScrollArea->setMinimumHeight(200);
}

void WaitingRoomDialog::setupButtons() {
    buttonLayout = new QHBoxLayout();
    buttonLayout->setSpacing(10);

    readyBtn = new QPushButton("✅ I'm Ready!");
    readyBtn->setStyleSheet("QPushButton { background-color: #4CAF50; } QPushButton:hover { background-color: #45a049; }");

    QPushButton* exitBtn = new QPushButton("❌ Leave Room");
    exitBtn->setStyleSheet("QPushButton { background-color: #f44336; } QPushButton:hover { background-color: #da190b; }");

    connect(readyBtn, &QPushButton::clicked, this, &WaitingRoomDialog::onReadyClicked);
    connect(exitBtn, &QPushButton::clicked, this, &WaitingRoomDialog::onExitClicked);

    buttonLayout->addWidget(readyBtn);
    buttonLayout->addWidget(exitBtn);
}

void WaitingRoomDialog::startPolling() {
    roomWaiter = std::thread(&WaitingRoomDialog::pollLobby, this);
}

void WaitingRoomDialog::stopPolling() {
    shouldStop = true;
    if (roomWaiter.joinable()) {
        roomWaiter.join();
    }
}

void WaitingRoomDialog::pollLobby() {
    std::vector<std::string> lastKnownPlayerNames;

    while (!shouldStop && !gameStarted) {
        try {
            GameLobbyDTO lobby = protocol.getGameLobby();
            MapType mapType = lobby.mapType;

            // Verificar si cambió la lista de jugadores
            std::vector<std::string> currentPlayerNames;
            for (const auto& player : lobby.playersChoices) {
                currentPlayerNames.push_back(player.playerName);
            }

            std::sort(currentPlayerNames.begin(), currentPlayerNames.end());
            std::sort(lastKnownPlayerNames.begin(), lastKnownPlayerNames.end());

            if (currentPlayerNames != lastKnownPlayerNames) {
                lastKnownPlayerNames = currentPlayerNames;

                // Actualizar UI en el hilo principal
                QMetaObject::invokeMethod(this, [this, players = lobby.playersChoices]() {
                    updatePlayerList(players);
                }, Qt::QueuedConnection);
            }

            // Verificar si el juego está listo para empezar
            if (lobby.status == READY_STATUS && !gameStarted) {
                gameStarted = true;

                QMetaObject::invokeMethod(this, [this, &mapType]() {
                    handleGameStart(mapType);
                }, Qt::QueuedConnection);

                return;
            }

        } catch (const std::exception& e) {
            if (!shouldStop) {
                QMetaObject::invokeMethod(this, [this, error = std::string(e.what())]() {
                    handleConnectionError(error);
                }, Qt::QueuedConnection);
            }
            return;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}

void WaitingRoomDialog::updatePlayerList(const std::vector<PlayerChoicesDTO>& readyPlayers) {
    clearPlayerLabels();

    int totalPlayers = readyPlayers.size() + (isLocalPlayerInList(readyPlayers) ? 0 : 1);
    setWindowTitle(QString("⌛ Waiting Room (%1 players)").arg(totalPlayers));

    updateSelfPlayerDisplay();

    TeamMapper teamMapper;
    SkinMapper skinMapper;

    for (const auto& player : readyPlayers) {
        if (player.playerName == playerName.toStdString()) {
            continue;
        }

        QString name = QString::fromStdString(player.playerName);
        QString team = teamMapper.toString(player.team);
        QString skin = skinMapper.toString(player.skin);

        QLabel* label = createPlayerLabel(name, team, skin, true);
        playersLayout->addWidget(label);
        playerLabels.push_back(label);
    }

    playersLayout->addStretch();
}

void WaitingRoomDialog::updateSelfPlayerDisplay() {
    // Eliminar label anterior del jugador local si existe
    if (!playerLabels.empty() && playerLabels[0]->styleSheet().contains("font-weight: bold")) {
        playersLayout->removeWidget(playerLabels[0]);
        delete playerLabels[0];
        playerLabels.erase(playerLabels.begin());
    }

    QString status = isReady ? "[Ready ✅]" : "[Waiting ⏳]";
    QString color = isReady ? "#4CAF50" : "#FFC107";

    QLabel* selfLabel = createPlayerLabel(playerName, teamStr, skinStr, isReady, true);

    // Insertar al principio
    playersLayout->insertWidget(0, selfLabel);
    playerLabels.insert(playerLabels.begin(), selfLabel);
}

QLabel* WaitingRoomDialog::createPlayerLabel(const QString& name, const QString& team,
                                             const QString& skin, bool ready, bool isSelf) {
    QString status = ready ? "[Ready ✅]" : "[Waiting ⏳]";
    QString labelText = QString("%1 — Team: %2 — Skin: %3 — %4").arg(name, team, skin, status);

    QLabel* label = new QLabel(labelText);

    QString baseStyle = "padding: 8px; margin: 2px; border-radius: 4px; ";

    if (isSelf) {
        QString color = ready ? "#4CAF50" : "#FFC107";
        label->setStyleSheet(baseStyle + QString("font-weight: bold; color: %1; background-color: rgba(255,255,255,0.1);").arg(color));
    } else {
        label->setStyleSheet(baseStyle + "color: #4CAF50; background-color: rgba(76,175,80,0.1);");
    }

    return label;
}

bool WaitingRoomDialog::isLocalPlayerInList(const std::vector<PlayerChoicesDTO>& players) {
    for (const auto& player : players) {
        if (player.playerName == playerName.toStdString()) {
            return true;
        }
    }
    return false;
}

void WaitingRoomDialog::clearPlayerLabels() {
    for (QLabel* label : playerLabels) {
        playersLayout->removeWidget(label);
        delete label;
    }
    playerLabels.clear();
}

void WaitingRoomDialog::handleGameStart(const MapType& mapType) {
    setWindowTitle("🎮 Starting Game...");
    readyBtn->setEnabled(false);
    readyBtn->setText("🚀 Game Starting...");
    readyBtn->setStyleSheet("QPushButton { background-color: #FF9800; }");

    clearPlayerLabels();

    QLabel* startingLabel = new QLabel("All players ready!\nStarting game...");
    startingLabel->setStyleSheet("font-weight: bold; color: #4CAF50; font-size: 18px; "
                                 "padding: 20px; text-align: center; background-color: rgba(76,175,80,0.2); "
                                 "border-radius: 8px;");
    startingLabel->setAlignment(Qt::AlignCenter);
    playersLayout->addWidget(startingLabel);

    QTimer::singleShot(2000, this, [this, &mapType]() {
        closeMenuAndStartGame(mapType);
    });
}

void WaitingRoomDialog::closeMenuAndStartGame(const MapType& mapType) {
    if (menu && menu->getMusicManager()) {
        menu->getMusicManager()->setVolume(0.0f);
    }

    this->accept();

    try {
        GameClient gameClient(protocol);
        gameClient.run(mapType);



    } catch (const std::exception& e) {
        QMessageBox::critical(this, "Game Error",
                              QString("Failed to start game: %1").arg(e.what()));

    }
    restoreMenu();
}

void WaitingRoomDialog::handleConnectionError(const std::string& error) {
    QMessageBox::warning(this, "Connection Error",
                         QString("Lost connection to server: %1").arg(QString::fromStdString(error)));
    this->reject();
}

void WaitingRoomDialog::restoreMenu() {
    std::cout << "restore menu" << std::endl;
    if (menu) {
        std::cout << "adentro if  restore" << std::endl;
        menu->getMusicManager()->setVolume(0.4f);
        std::cout << " music" << std::endl;
        menu->show();
        std::cout << "show" << std::endl;
        menu->raise();
        std::cout << "raise" << std::endl;
        menu->activateWindow();
        std::cout << "active windowu" << std::endl;
    }
}


void WaitingRoomDialog::onReadyClicked() {
    if (isReady) {
        return;
    }

    readyBtn->setEnabled(false);
    readyBtn->setText("⏳ Sending...");

    std::thread([this]() {
        try {
            TeamMapper teamMapper;
            SkinMapper skinMapper;

            Team team = teamMapper.fromString(teamStr);
            Skin skin = static_cast<Skin>(skinMapper.toSkinId(skinStr));

            PlayerChoicesDTO playerChoice(playerName.toStdString(), team, skin);

            // Enviar estado ready al servidor
            protocol.ready(playerChoice);

            // Actualizar UI en el hilo principal
            QMetaObject::invokeMethod(this, [this]() {
                isReady = true;
                readyBtn->setText("✅ Ready! (Waiting for others...)");
                readyBtn->setStyleSheet("QPushButton { background-color: #4CAF50; }");

                // Actualizar display del jugador local
                updateSelfPlayerDisplay();

                QLabel* confirmLabel = new QLabel("✅ You are ready! Waiting for other players...");
                confirmLabel->setStyleSheet("color: #4CAF50; font-style: italic; padding: 8px; "
                                            "background-color: rgba(76,175,80,0.1); border-radius: 4px;");
                playersLayout->addWidget(confirmLabel);

            }, Qt::QueuedConnection);

        } catch (const std::exception& e) {
            QMetaObject::invokeMethod(this, [this, error = std::string(e.what())]() {
                readyBtn->setEnabled(true);
                readyBtn->setText("✅ I'm Ready!");
                QMessageBox::warning(this, "Error",
                                     QString("Failed to send ready status: %1").arg(QString::fromStdString(error)));
            }, Qt::QueuedConnection);
        }
    }).detach();
}

void WaitingRoomDialog::onExitClicked() {
    shouldStop = true;

    std::thread([this]() {
        try {
            protocol.leaveGameLobby();
        } catch (...) {
        }
    }).detach();

    if (menu) {
        menu->close();
    }

    this->reject();
}

void WaitingRoomDialog::closeEvent(QCloseEvent* event) {
    shouldStop = true;

    std::thread([this]() {
        try {
            protocol.leaveGameLobby();
        } catch (...) {}
    }).detach();

    QDialog::closeEvent(event);
    restoreMenu(); //TODO VER SI ESTA BIEN!!!!
}
