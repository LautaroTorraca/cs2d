#include "GameFlowUtils.h"

#include <stdexcept>
#include "Login/Dialogs/CreateGameDialog.h"
#include "Login/Dialogs/GameNameDialog.h"
#include "Login/Dialogs/MapSelectionDialog.h"
#include "Login/Dialogs/SkinSelectionDialog.h"
#include "Login/Dialogs/TeamSelectionDialog.h"
#include "Login/Mappers/SkinTraslator.h"
#include "Login/Mappers/MapMapper.h"
#include "Login/MessageBox.h"

QString GameFlowUtils::getUsername(QLineEdit* input, QWidget* parent) {
    QString name = input->text().trimmed();
    if (name.isEmpty()) {
        MessageBox msg(parent);
        msg.showMessage("Name Required", "Please enter your name to continue.", MessageType::Warning);
    }
    return name;
}

QString GameFlowUtils::askGameName(QWidget* parent) {
    GameNameDialog dialog(parent, "Enter a name for your new game:", "Create");
    int result = dialog.exec();
    if (result != QDialog::Accepted) {
        throw std::runtime_error("Game name selection cancelled");
    }

    QString name = dialog.getGameName();

    if (name.isEmpty()) {
        throw std::runtime_error("Game name cannot be empty");
    }

    return name;
}

MapType GameFlowUtils::askMap(QWidget* parent) {
    MapSelectionDialog dialog(parent);
    int result = dialog.exec();
    if (result != QDialog::Accepted) {
        throw std::runtime_error("Map selection cancelled");
    }

    MapMapper mapper;
    return mapper.toMap(dialog.getSelectedMap());
}

std::pair<uint8_t, uint8_t> GameFlowUtils::askConfig(QWidget* parent) {
    CreateGameDialog dialog(parent);
    int result = dialog.exec();
    if (result != QDialog::Accepted) {
        throw std::runtime_error("Game configuration cancelled");
    }

    uint8_t players = dialog.getGameConfig().playerCount;
    uint8_t rounds = dialog.getGameConfig().rounds;
    return {players, rounds};
}

Team GameFlowUtils::askTeam(QWidget* parent) {
    TeamSelectionDialog dialog(parent);
    int result = dialog.exec();
    if (result != QDialog::Accepted) {
        throw std::runtime_error("Team selection cancelled");
    }

    return dialog.getSelectedTeam();
}

Skin GameFlowUtils::askSkin(uint8_t teamId, QWidget* parent) {
    SkinSelectionDialog dialog(teamId, parent);
    int result = dialog.exec();
    if (result != QDialog::Accepted) {
        throw std::runtime_error("Skin selection cancelled");
    }
    return static_cast<Skin>(dialog.getSelectedSkin());
}

void GameFlowUtils::showError(QWidget* parent, const QString& title, const QString& message) {
    MessageBox msg(parent);
    msg.showMessage(title, message, MessageType::Error);
}
