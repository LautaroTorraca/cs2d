#ifndef JOINGAMEBUTTON_H
#define JOINGAMEBUTTON_H

#include "GameMenuButton.h"
#include <QLineEdit>

class JoinGameButton : public GameMenuButton {
Q_OBJECT

public:
    JoinGameButton(QWidget* parent, QLineEdit* usernameInput);

private slots:
    void handleClick();

private:
    QLineEdit* usernameInput;
};

#endif // JOINGAMEBUTTON_H
