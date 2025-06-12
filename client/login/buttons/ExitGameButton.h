#ifndef EXITGAMEBUTTON_H
#define EXITGAMEBUTTON_H

#include "GameMenuButton.h"

class ExitGameButton : public GameMenuButton {
Q_OBJECT

public:
    explicit ExitGameButton(QWidget* parent = nullptr);

private slots:
    void handleClick();
};

#endif // EXITGAMEBUTTON_H
