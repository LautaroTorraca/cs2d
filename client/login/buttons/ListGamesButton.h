#ifndef LISTGAMESBUTTON_H
#define LISTGAMESBUTTON_H

#include "GameMenuButton.h"

class ListGamesButton : public GameMenuButton {
Q_OBJECT

public:
    explicit ListGamesButton(QWidget* parent = nullptr);

private slots:
    void handleClick();
};

#endif // LISTGAMESBUTTON_H
