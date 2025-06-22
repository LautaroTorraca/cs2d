#include "WaitingRoomDialog.h"

#include <QHBoxLayout>
#include <QMessageBox>
#include <QMetaObject>
#include <QPushButton>
#include <QVBoxLayout>
#include <algorithm>
#include <atomic>
#include <chrono>
#include <set>
#include <thread>

#include "Login/Mappers/SkinTraslator.h"
#include "Login/Mappers/TeamMapper.h"

#include "GameClient.h"
using namespace Client;


WaitingRoomDialog::WaitingRoomDialog(const QString& playerName,
                                     const QString& teamStr,
                                     const QString& skinStr,
                                     Protocol& protocol,
                                     QWidget* parent)
        : QDialog(parent),
        playerName(playerName),
        teamStr(teamStr),
        skinStr(skinStr),
        protocol(protocol),
        shouldStop(false),
        isReady(false) {

    setWindowTitle("⌛ Waiting Room");
    resize(440, 360);
    setModal(true);

    setupUI();

    roomWaiter = std::thread(&WaitingRoomDialog::pollLobby, this);
}

WaitingRoomDialog::~WaitingRoomDialog() {
    shouldStop = true;

    if (roomWaiter.joinable()) {
        roomWaiter.join();
    }
}

void WaitingRoomDialog::setupUI() {
    setStyleSheet(R"(
        QWidget {
            background-color: #121212;
            color: #f0f0f0;
            font-family: 'Segoe UI', sans-serif;
            font-size: 15px;
        }
        QLabel {
            padding: 6px;
        }
        QPushButton {
            background-color: #1e88e5;
            color: white;
            border-radius: 6px;
            padding: 8px 16px;
            margin: 10px 10px 0px 0px;
        }
        QPushButton:hover {
            background-color: #1565c0;
        }
        QPushButton:disabled {
            background-color: #555555;
            color: #aaaaaa;
        }
    )");

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->setContentsMargins(20, 20, 20, 20);

    QLabel* title = new QLabel("Players in the Room:");
    title->setStyleSheet("font-weight: bold; font-size: 16px;");
    layout->addWidget(title);

    playersScrollArea = new QScrollArea();
    playersWidget = new QWidget();

    playersLayout = new QVBoxLayout();
    playersWidget->setLayout(playersLayout);

    playersScrollArea->setWidget(playersWidget);
    playersScrollArea->setWidgetResizable(true);
    layout->addWidget(playersScrollArea);

    // Muestro el jugador a entrar
    QString selfEntry = QString("%1 - Team: %2 - Skin: %3 - [Waiting ⏳]").arg(playerName, teamStr, skinStr);
    QLabel* selfLabel = new QLabel(selfEntry);
    selfLabel->setStyleSheet("font-weight: bold; color: #FFC107;");
    playersLayout->addWidget(selfLabel);
    playerLabels.push_back(selfLabel);

    QHBoxLayout* buttonLayout = new QHBoxLayout();

    readyBtn = new QPushButton("✅ Ready");
    QPushButton* exitBtn = new QPushButton("❌ Exit");

    connect(readyBtn, &QPushButton::clicked, this, &WaitingRoomDialog::onReadyClicked);
    connect(exitBtn, &QPushButton::clicked, this, &WaitingRoomDialog::onExitClicked);

    buttonLayout->addWidget(readyBtn);
    buttonLayout->addWidget(exitBtn);
    layout->addLayout(buttonLayout);
}

void WaitingRoomDialog::pollLobby() {
    std::vector<std::string> lastKnownPlayerNames;

    while (!shouldStop) {
        try {
            GameLobbyDTO lobby = protocol.getGameLobby();

            std::vector<std::string> currentPlayerNames;
            for (const auto& player : lobby.playersChoices) {
                currentPlayerNames.push_back(player.playerName);
            }

            std::sort(currentPlayerNames.begin(), currentPlayerNames.end());
            std::sort(lastKnownPlayerNames.begin(), lastKnownPlayerNames.end());

            if (currentPlayerNames != lastKnownPlayerNames) {
                lastKnownPlayerNames = currentPlayerNames;

                // UI update en hilo main
                QMetaObject::invokeMethod(this, [this, players = lobby.playersChoices]() {
                    updatePlayerList(players);
                }, Qt::QueuedConnection);
            }

            if (lobby.status == READY_STATUS) {
                QMetaObject::invokeMethod(this, [this]() {
                    setWindowTitle("🎮 Starting Game...");
                    readyBtn->setEnabled(false);
                    readyBtn->setText("Starting Game...");

                    QLabel* startingLabel = new QLabel("All players ready! Game starting...");
                    startingLabel->setStyleSheet("font-weight: bold; color: #4CAF50; font-size: 16px; padding: 10px;");
                    playersLayout->addWidget(startingLabel);

                }, Qt::QueuedConnection);

                std::this_thread::sleep_for(std::chrono::milliseconds(2000));

                QMetaObject::invokeMethod(this, [this]() {
                    this->accept();
                    GameClient gameClient(this->protocol);
                    gameClient.run();
                    this->hide();

                }, Qt::QueuedConnection);
                return;
            }

        } catch (const std::exception& e) {
            QMetaObject::invokeMethod(this, [this, error = std::string(e.what())]() {
                QMessageBox::warning(this, "Connection Error",
                                     QString("Lost connection to server: %1").arg(QString::fromStdString(error)));
                this->reject();
            }, Qt::QueuedConnection);
            return;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}

void WaitingRoomDialog::updatePlayerList(const std::vector<PlayerChoicesDTO>& readyPlayers) {
    TeamMapper teamMapper;
    SkinMapper skinMapper;

    for (QLabel* label : playerLabels) {
        playersLayout->removeWidget(label);
        delete label;
    }
    playerLabels.clear();

    bool localPlayerReady = false;
    for (const auto& player : readyPlayers) {
        if (player.playerName == playerName.toStdString()) {
            localPlayerReady = true;
            break;
        }
    }

    QString selfEntry = QString("%1 — Team: %2 — Skin: %3").arg(playerName, teamStr, skinStr);
    if (localPlayerReady) {
        selfEntry += " — [Ready ✅]";
    } else {
        selfEntry += " — [Waiting ⏳]";
    }

    QLabel* selfLabel = new QLabel(selfEntry);
    if (localPlayerReady) {
        selfLabel->setStyleSheet("font-weight: bold; color: #4CAF50;"); // Verde para ready
    } else {
        selfLabel->setStyleSheet("font-weight: bold; color: #FFC107;"); // Amarillo para waiting
    }
    playersLayout->addWidget(selfLabel);
    playerLabels.push_back(selfLabel);

    for (const auto& player : readyPlayers) {
        if (player.playerName == playerName.toStdString()) {
            continue;
        }

        QString name = QString::fromStdString(player.playerName);
        QString team = teamMapper.toString(player.team);
        QString skin = skinMapper.toString(player.skin);

        QString labelText = QString("%1 — Team: %2 — Skin: %3 — [Ready ✅]").arg(name, team, skin);

        QLabel* label = new QLabel(labelText);
        label->setStyleSheet("color: #4CAF50;");

        playersLayout->addWidget(label);
        playerLabels.push_back(label);
    }

    int totalReadyPlayers = readyPlayers.size();
    setWindowTitle(QString("⌛ Waiting Room (%1 ready)").arg(totalReadyPlayers));
}

void WaitingRoomDialog::onReadyClicked() {
    if (isReady) {
        return;
    }

    try {
        TeamMapper teamMapper;
        SkinMapper skinMapper;

        Team team = teamMapper.fromString(teamStr);
        Skin skin = static_cast<Skin>(skinMapper.toSkinId(skinStr));

        PlayerChoicesDTO playerChoice(playerName.toStdString(), team, skin);

        std::thread([this, playerChoice]() {
            try {
                protocol.ready(playerChoice);
                QMetaObject::invokeMethod(this, [this]() {
                    isReady = true;
                    readyBtn->setText("✅ Ready (Waiting for others...)");
                    readyBtn->setEnabled(false);

                    // muestro que estoy ready
                    QLabel* confirmLabel = new QLabel("✅ You are ready! Waiting for other players...");
                    confirmLabel->setStyleSheet("color: #4CAF50; font-style: italic; padding: 5px;");
                    playersLayout->addWidget(confirmLabel);

                }, Qt::QueuedConnection);

            } catch (const std::exception& e) {
                QMetaObject::invokeMethod(this, [this, error = std::string(e.what())]() {
                    QMessageBox::warning(this, "Error",
                                         QString("Failed to send ready status: %1").arg(QString::fromStdString(error)));
                }, Qt::QueuedConnection);
            }
        }).detach();

    } catch (const std::exception& e) {
        QMessageBox::warning(this, "Error",
                             QString("Failed to prepare ready status: %1").arg(e.what()));
    }
}

void WaitingRoomDialog::onExitClicked() {
    shouldStop = true;
    std::thread([this]() {
        try {
            protocol.exit();
        } catch (...) {}
    }).detach();

    this->reject();
}

void WaitingRoomDialog::closeEvent(QCloseEvent* event) {
    shouldStop = true;
    QDialog::closeEvent(event);
}
