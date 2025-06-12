#include "CreateGameButton.h"
#include "login/dialogs/MapSelectionDialog.h"
#include "login/dialogs/CreateGameDialog.h"
#include "login/dialogs/TeamSelectionDialog.h"
#include "login/dialogs/SkinSelectionDialog.h"
#include "login/dialogs/WaitingRoomDialog.h"

#include "../MessageBox.h"
#include "../SkinTraslator.h"
#include "login/mocks/TeamConstantsMock.h"

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
        //Seleccion de mapa
        MapSelectionDialog mapDialog(this->parentWidget());
        if (mapDialog.exec() != QDialog::Accepted) {
            return;
        }
        MapType selectedMap = static_cast<MapType>(mapDialog.getSelectedMap());

        //Configuración de partida
        CreateGameDialog configDialog(this->parentWidget());
        if (configDialog.exec() != QDialog::Accepted) {
            return;
        }

        int maxPlayers = configDialog.getGameConfig().playerCount;
        int rounds = configDialog.getGameConfig().rounds;

        //Seleccion de equipo
        TeamSelectionDialog teamDialog(this->parentWidget());
        if (teamDialog.exec() != QDialog::Accepted) {
            return;
        }

        QString selectedTeam = teamDialog.getSelectedTeam();
        uint8_t teamId = 0;
        if (selectedTeam == "CT") {
            teamId = TeamConstants::COUNTER_TERRORISTS;
        } else {
            teamId = TeamConstants::TERRORISTS;
        }

        //Selección de skin
        SkinSelectionDialog skinDialog(teamId, this->parentWidget());
        if (skinDialog.exec() != QDialog::Accepted) {
            return;
        }
        uint8_t selectedSkinId = skinDialog.getSelectedSkin();

        // Crear el GameDTO
        GameDTO gameDto(name, selectedMap, 1, maxPlayers, rounds);

        // TODO: enviar gameDto al servidor y crear partida

        //Mostrar sala de espera
        SkinMapper mapper;
        QString skinText = mapper.toString(mapper.toSkin(selectedSkinId));

        WaitingRoomDialog waitingRoom(gameDto, name, selectedTeam, skinText, this->parentWidget());
        waitingRoom.exec();

    } catch (const std::exception& e) {
        MessageBox msg(this);
        msg.showMessage("❌ Failed to Create Game",
                        QString("An unexpected error occurred:\n\n%1").arg(e.what()),
                        MessageType::Error);
    }
}
