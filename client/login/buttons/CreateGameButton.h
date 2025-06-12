#ifndef CREATEGAMEBUTTON_H
#define CREATEGAMEBUTTON_H

#include "GameMenuButton.h"
#include <QLineEdit>
#include <QObject>

class CreateGameButton : public GameMenuButton {
Q_OBJECT

public:
    CreateGameButton(QWidget* parent, QLineEdit* usernameInput);

private slots:
    void handleClick();

private:
    QLineEdit* usernameInput;
};

#endif // CREATEGAMEBUTTON_H
