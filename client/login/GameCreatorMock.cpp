#include "GameCreatorMock.h"
#include "CreateGameDialog.h"

GameDTO GameCreatorMock::openCreateGameDialog(QWidget *parent) {
    CreateGameDialog dialog(parent);
    if (dialog.exec() == QDialog::Accepted) {
        return dialog.getGameConfig();
    }
    return GameDTO();
}
