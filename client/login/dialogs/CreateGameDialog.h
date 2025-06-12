#ifndef CREATE_GAME_DIALOG_H
#define CREATE_GAME_DIALOG_H

#include <QDialog>
#include "login/mocks/GameDTO.h"

class QSpinBox;
class QPushButton;
class QVBoxLayout;

class CreateGameDialog : public QDialog {
Q_OBJECT

public:
    explicit CreateGameDialog(QWidget *parent = nullptr);
    GameDTO getGameConfig() const;

private slots:
    void handleConfirm();

private:
    QSpinBox *playerSpinBox;
    QSpinBox *roundsSpinBox;
    QPushButton *confirmButton;

    GameDTO config;
};

#endif // CREATE_GAME_DIALOG_H
