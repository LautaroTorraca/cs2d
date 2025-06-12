#include "WaitingRoomDialog.h"
#include "../SkinTraslator.h"
#include "login/mocks/TeamConstantsMock.h"

#include <QVBoxLayout>
#include <QLabel>
#include <QString>
#include <QTimer>
#include <QRandomGenerator>

WaitingRoomDialog::WaitingRoomDialog(const GameDTO &config, const QString &playerName,
                                     const QString &team, const QString &skin,
                                     QWidget *parent)
        : QDialog(parent) {
    setWindowTitle("⌛ Waiting Room");
    resize(440, 320);
    setModal(true);

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
    )");

    auto *layout = new QVBoxLayout(this);
    layout->setContentsMargins(20, 20, 20, 20);

    auto *title = new QLabel("Players in the Room:");
    title->setStyleSheet("font-weight: bold; font-size: 18px; margin-bottom: 12px;");
    layout->addWidget(title);

    playersLayout = new QVBoxLayout();
    layout->addLayout(playersLayout);

    populateInitialPlayer(playerName, team, skin);
    simulateOtherPlayersJoining(config.playerCount - 1);
}

void WaitingRoomDialog::populateInitialPlayer(const QString &name, const QString &team, const QString &skin) {
    auto *label = new QLabel(QString("%1 — Team: %2 — Skin: %3").arg(name, team, skin));
    playersLayout->addWidget(label);
    playerLabels.push_back(label);
}

void WaitingRoomDialog::simulateOtherPlayersJoining(int total) {
    QStringList fakeNames = {"Alex", "Charlie", "Jordan", "Morgan", "Sam", "Taylor", "Jamie", "Robin"};

    for (int i = 0; i < total; ++i) {
        QTimer::singleShot(1000 * (i + 1), this, [this, fakeNames]() {
            QString name = fakeNames.at(QRandomGenerator::global()->bounded(fakeNames.size()));

            QString team;
            int teamValue = QRandomGenerator::global()->bounded(2);
            if (teamValue == 0) {
                team = "CT";
            } else {
                team = "TT";
            }

            uint8_t skinId;
            if (team == "CT") {
                QList<uint8_t> ctSkins;
                ctSkins.append(SkinConstants::SEAL_FORCE);
                ctSkins.append(SkinConstants::GERMAN_GSG9);
                ctSkins.append(SkinConstants::UK_SAS);
                ctSkins.append(SkinConstants::FRENCH_GIGN);
                skinId = ctSkins.at(QRandomGenerator::global()->bounded(ctSkins.size()));
            } else {
                QList<uint8_t> ttSkins;
                ttSkins.append(SkinConstants::PHOENIX);
                ttSkins.append(SkinConstants::L337_KREW);
                ttSkins.append(SkinConstants::ARCTIC_AVENGER);
                ttSkins.append(SkinConstants::GUERRILLA);
                skinId = ttSkins.at(QRandomGenerator::global()->bounded(ttSkins.size()));
            }

            SkinMapper mapper;
            QString skinName = mapper.toString(mapper.toSkin(skinId));

            QLabel *label = new QLabel(QString("🕓 %1 — Team: %2 — Skin: %3").arg(name, team, skinName));
            playersLayout->addWidget(label);
            playerLabels.push_back(label);
        });
    }
}
