#include "WaitingRoomDialog.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QString>
#include <QTimer>
#include <QRandomGenerator>

WaitingRoomDialog::WaitingRoomDialog(const GameDTO &config, const QString &playerName,
                                     const QString &team, const QString &skin,
                                     QWidget *parent)
    : QDialog(parent) {
    setWindowTitle("Waiting Room");
    resize(400, 300);
    setModal(true);

    auto *layout = new QVBoxLayout(this);
    auto *title = new QLabel("Players in the Room:");
    title->setStyleSheet("font-weight: bold; font-size: 16px;");
    layout->addWidget(title);

    playersLayout = new QVBoxLayout();
    layout->addLayout(playersLayout);

    populateInitialPlayer(playerName, team, skin);

    // Simulate N-1 players joining (only fake)
    simulateOtherPlayersJoining(config.playerCount - 1);
}

void WaitingRoomDialog::populateInitialPlayer(const QString &name, const QString &team, const QString &skin) {
    auto *label = new QLabel(QString("🧑 %1 - Team: %2 - Skin: %3").arg(name, team, skin));
    playersLayout->addWidget(label);
    playerLabels.push_back(label);
}

void WaitingRoomDialog::simulateOtherPlayersJoining(int total) {
    QStringList names = {"Alex", "Charlie", "Jordan", "Morgan", "Sam", "Taylor", "Jamie", "Robin"};
    QStringList skins = {"Urban", "FBI", "Phoenix", "Elite", "Guerrilla"};
    QStringList teams = {"CT", "TT"};

    for (int i = 0; i < total; ++i) {
        QTimer::singleShot(1000 * (i + 1), this, [=]() {
            QString name = names.at(QRandomGenerator::global()->bounded(names.size()));
            QString team = teams.at(QRandomGenerator::global()->bounded(teams.size()));
            QString skin = skins.at(QRandomGenerator::global()->bounded(skins.size()));

            auto *label = new QLabel(QString("🧑 %1 - Team: %2 - Skin: %3").arg(name, team, skin));
            playersLayout->addWidget(label);
            playerLabels.push_back(label);
        });
    }
}
