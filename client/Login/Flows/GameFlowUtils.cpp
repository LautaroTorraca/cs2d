#include "GameFlowUtils.h"

#include <stdexcept>
#include "client/Login/Dialogs/CreateGameDialog.h"
#include "client/Login/Dialogs/GameNameDialog.h"
#include "client/Login/Dialogs/MapSelectionDialog.h"
#include "client/Login/Dialogs/SkinSelectionDialog.h"
#include "client/Login/Dialogs/TeamSelectionDialog.h"
#include "client/Login/Mappers/SkinTraslator.h"
#include "client/Login/Mappers/MapMapper.h"
#include "client/Login/MessageBox.h"

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
    return dialog.getGameName();
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
