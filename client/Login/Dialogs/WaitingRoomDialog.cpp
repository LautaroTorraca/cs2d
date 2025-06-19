#include "WaitingRoomDialog.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QTimer>
#include <QVBoxLayout>
#include <thread>
#include <chrono>

#include "../SkinTraslator.h"
#include "server/Team.h"

WaitingRoomDialog::WaitingRoomDialog(const QString& playerName,
                                     const QString& team,
                                     const QString& skin,
                                     Protocol& protocol,
                                     QWidget* parent)
        : playerName(playerName.toStdString()), team(team.toUInt()), skin(skin.toUInt()), QDialog(parent), protocol(protocol) {
    setWindowTitle("⌛ Waiting Room");
    resize(440, 360);
    setModal(true);

    setupUI(playerName, team, skin);

    // Iniciar hilo de polling
    this->roomWaiter = std::thread(&WaitingRoomDialog::pollLobby, this);
}

WaitingRoomDialog::~WaitingRoomDialog() {
    if (roomWaiter.joinable()) {
        roomWaiter.join();
    }
}

void WaitingRoomDialog::setupUI(const QString& playerName, const QString& team, const QString& skin) {
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
    )");

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->setContentsMargins(20, 20, 20, 20);

    QLabel* title = new QLabel("Players in the Room:");
    title->setStyleSheet("font-weight: bold; font-size: 18px; margin-bottom: 12px;");
    layout->addWidget(title);

    playersLayout = new QVBoxLayout();
    layout->addLayout(playersLayout);

    QString selfEntry = QString("%1 — Team: %2 — Skin: %3").arg(playerName, team, skin);
    QLabel* selfLabel = new QLabel(selfEntry);
    playersLayout->addWidget(selfLabel);
    playerLabels.push_back(selfLabel);

    QHBoxLayout* buttonsLayout = new QHBoxLayout();

    readyButton = new QPushButton("✅ Ready");
    exitButton = new QPushButton("❌ Exit");

    connect(readyButton, &QPushButton::clicked, this, &WaitingRoomDialog::onReadyClicked);
    connect(exitButton, &QPushButton::clicked, this, &WaitingRoomDialog::reject);

    buttonsLayout->addWidget(readyButton);
    buttonsLayout->addWidget(exitButton);
    layout->addLayout(buttonsLayout);
}

void WaitingRoomDialog::pollLobby() {
    while (true) {
        GameLobbyDTO lobby = protocol.getGameLobby();

        QMetaObject::invokeMethod(this, [this, lobby]() {
            updatePlayerList(lobby.playersChoices);
        }, Qt::QueuedConnection);

        if (lobby.status == READY_STATUS) {
            break;
        }

        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    GameLobbyDTO lobby = protocol.getGameLobby();
    QMetaObject::invokeMethod(this, [this, lobby]() {
        updatePlayerList(lobby.playersChoices);
        this->accept();
    }, Qt::QueuedConnection);
}

void WaitingRoomDialog::updatePlayerList(const std::vector<PlayerChoicesDTO>& players) {
    for (size_t i = 1; i < playerLabels.size(); ++i) {
        playersLayout->removeWidget(playerLabels[i]);
        delete playerLabels[i];
    }
    playerLabels.resize(1);

    SkinMapper mapper;

    for (const PlayerChoicesDTO& player : players) {
        QString name = QString::fromStdString(player.playerName);
        QString team = (player.team == Team::COUNTER_TERRORISTS) ? "CT" : "TT";
        QString skin = mapper.toString(static_cast<Skin>(player.skin));

        // Evitar duplicados
        bool alreadyListed = false;
        for (const auto& label : playerLabels) {
            if (label->text().startsWith(name)) {
                alreadyListed = true;
                break;
            }
        }
        if (alreadyListed) continue;

        QLabel* label = new QLabel(QString("%1 — Team: %2 — Skin: %3").arg(name, team, skin));
        playersLayout->addWidget(label);
        playerLabels.push_back(label);
    }
}

void WaitingRoomDialog::onReadyClicked() {
    PlayerChoicesDTO playerChoices(playerName, (Team)team, (Skin)skin);
    protocol.ready(playerChoices);

    readyButton->setText("✅ Esperando...");
    readyButton->setEnabled(false);
}
