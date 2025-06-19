#include "SkinSelectionDialog.h"

#include <QCoreApplication>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPixmap>
#include <QIcon>

#include "server/Skin.h"
#include "server/Team.h"

SkinSelectionDialog::SkinSelectionDialog(uint8_t team, QWidget* parent)
        : QDialog(parent), selectedSkin(0) {
    setWindowTitle("Select Skin");
    setModal(true);
    resize(680, 320);
    setupUI();
    loadSkinsForTeam(team);
    setupConnections();
    updateSkinImage(0);
}

void SkinSelectionDialog::setupUI() {
    setStyleSheet(R"(
        QWidget {
            background-color: #121212;
            color: #f0f0f0;
            font-family: 'Segoe UI', sans-serif;
            font-size: 16px;
        }

        QLabel {
            font-size: 18px;
            font-weight: 600;
            margin-top: 20px;
            margin-bottom: 8px;
        }

        QComboBox {
            background-color: #1f1f1f;
            color: white;
            border: 2px solid #444;
            border-radius: 8px;
            padding: 6px;
            font-size: 16px;
        }

        QPushButton {
            background-color: #007acc;
            color: white;
            border: none;
            border-radius: 10px;
            font-size: 17px;
            font-weight: bold;
            padding: 10px 20px;
            margin-top: 30px;
        }

        QPushButton:hover {
            background-color: #0095ff;
        }

        QPushButton:pressed {
            background-color: #005f99;
        }

        #skinImageLabel {
            border: 2px solid #444;
            border-radius: 8px;
            background-color: #1f1f1f;
            padding: 10px;
            min-width: 180px;
            min-height: 180px;
        }
    )");

    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(15);
    mainLayout->setContentsMargins(30, 30, 30, 30);

    QLabel* label = new QLabel("Choose your skin:");
    mainLayout->addWidget(label);

    QHBoxLayout* skinSelectionLayout = new QHBoxLayout();

    skinComboBox = new QComboBox(this);
    skinSelectionLayout->addWidget(skinComboBox);

    skinImageLabel = new QLabel(this);
    skinImageLabel->setObjectName("skinImageLabel");
    skinImageLabel->setAlignment(Qt::AlignCenter);
    skinImageLabel->setScaledContents(false);
    skinSelectionLayout->addWidget(skinImageLabel);

    mainLayout->addLayout(skinSelectionLayout);

    confirmButton = new QPushButton("Confirm");
    mainLayout->addWidget(confirmButton, 0, Qt::AlignCenter);
}

void SkinSelectionDialog::setupConnections() {
    connect(skinComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &SkinSelectionDialog::updateSkinImage);
    connect(confirmButton, &QPushButton::clicked, this, &SkinSelectionDialog::handleConfirm);
}

void SkinSelectionDialog::loadSkinsForTeam(uint8_t team) {
    skinComboBox->clear();
    skinPaths.clear();

    auto addSkin = [&](const QString& text, const QString& resourcePath, const QString& fallbackPath, uint8_t skinId) {
        skinComboBox->addItem(QIcon(resourcePath), text, skinId);
        skinPaths.append(resourcePath + "|" + fallbackPath);
    };

    if (team == Team::TERRORISTS) {
        addSkin("Phoenix", ":/skins/phoenix.png", "login/assets/skins/Phoenix.png", Skin::PHOENIX);
        addSkin("L337 Krew", ":/skins/l337.png", "login/assets/skins/L337 Krew.png", Skin::L337_KREW);
        addSkin("Arctic Avenger", ":/skins/arctic.png", "login/assets/skins/Artic Avenger.png", Skin::ARCTIC_AVENGER);
        addSkin("Guerrilla", ":/skins/guerrilla.png", "login/assets/skins/Guerrilla.png", Skin::GUERRILLA);
    } else if (team == Team::COUNTER_TERRORISTS) {
        addSkin("SEAL Force", ":/skins/sealforce.png", "login/assets/skins/SealForce.png", Skin::SEAL_FORCE);
        addSkin("German GSG9", ":/skins/gsg9.png", "login/assets/skins/German GSG-9.png", Skin::GERMAN_GSG9);
        addSkin("UK SAS", ":/skins/sas.png", "login/assets/skins/UK SAS.png", Skin::UK_SAS);
        addSkin("French GIGN", ":/skins/gign.png", "login/assets/skins/French GIGN.png", Skin::FRENCH_GIGN);
    }
}

void SkinSelectionDialog::updateSkinImage(int index) {
    if (index < 0 || index >= skinPaths.size()) {
        skinImageLabel->setText("No Image Available");
        return;
    }

    const QStringList parts = skinPaths[index].split("|");
    const QString& resourcePath = parts[0];
    const QString& fallbackPath = parts[1];

    QPixmap pixmap(resourcePath);
    if (pixmap.isNull()) {
        QString appDir = QCoreApplication::applicationDirPath();
        QStringList fallbacks = {
                appDir + "/" + fallbackPath,
                "../client/" + fallbackPath,
                fallbackPath
        };
        for (const QString& path : fallbacks) {
            pixmap = QPixmap(path);
            if (!pixmap.isNull()) break;
        }
    }

    if (!pixmap.isNull()) {
        QPixmap scaledPixmap = pixmap.scaled(160, 160, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        skinImageLabel->setPixmap(scaledPixmap);
    } else {
        skinImageLabel->setText("Image not found");
    }
}

void SkinSelectionDialog::handleConfirm() {
    selectedSkin = static_cast<uint8_t>(skinComboBox->currentData().toInt());
    accept();
}

uint8_t SkinSelectionDialog::getSelectedSkin() const {
    return selectedSkin;
}
