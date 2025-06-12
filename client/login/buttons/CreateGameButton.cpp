#include "CreateGameButton.h"
#include "login/mocks/GameCreatorMock.h"
#include "login/dialogs/TeamSelectionDialog.h"
#include "login/dialogs/SkinSelectionDialog.h"
#include "login/dialogs/WaitingRoomDialog.h"
#include "../SkinTraslator.h"
#include "../MessageBox.h"
#include "login/mocks/CreateGameDTO.h"
#include "login/mocks/TeamConstantsMock.h"

#include <QDebug>

CreateGameButton::CreateGameButton(QWidget* parent, QLineEdit* usernameInput)
        : GameMenuButton("➕  Create Game", parent), usernameInput(usernameInput) {
    connect(this, &QPushButton::clicked, this, &CreateGameButton::handleClick);
}

void CreateGameButton::handleClick() {
    QString name = usernameInput->text().trimmed();
    if (name.isEmpty()) {
        MessageBox msg(this);
        msg.showMessage("Name Required", "Please enter your name to continue.", MessageType::Warning);
        return;
    }

    try {
        GameCreatorMock gameCreator;
        GameDTO dto = gameCreator.openCreateGameDialog(this->parentWidget());

        TeamSelectionDialog teamDialog(this->parentWidget());
        if (teamDialog.exec() != QDialog::Accepted) return;

        QString selectedTeam = teamDialog.getSelectedTeam();

        uint8_t teamId = 0;
        if (selectedTeam == "CT") {
            teamId = TeamConstants::COUNTER_TERRORISTS;
        } else {
            teamId = TeamConstants::TERRORISTS;
        }

        SkinSelectionDialog skinDialog(teamId, this->parentWidget());
        if (skinDialog.exec() != QDialog::Accepted) return;

        uint8_t selectedSkinId = skinDialog.getSelectedSkin();

        // TODO revisar CreateGameDTO
        CreateGameDTO createDto;
        createDto.playerName = name;
        createDto.team = selectedTeam;
        createDto.skinId = selectedSkinId;
        createDto.playerCount = dto.playerCount;
        createDto.maxPlayers = dto.maxPlayers;
        createDto.rounds = dto.rounds;

        // TODO: Enviar createDto al servidor

        // Mostrar waiting room
        SkinMapper mapper;
        QString skinText = mapper.toString(mapper.toSkin(selectedSkinId));
        WaitingRoomDialog waitingRoom(dto, name, selectedTeam, skinText, this->parentWidget());
        waitingRoom.exec();


    } catch (const std::exception& e) {
        MessageBox msg(this);
        msg.showMessage("❌ Failed to Create Game",
                        QString("An unexpected error occurred:\n\n%1").arg(e.what()),
                        MessageType::Error);
    }
}
