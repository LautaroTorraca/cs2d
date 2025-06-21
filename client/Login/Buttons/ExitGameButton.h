#pragma once
#include "GameMenuButton.h"

class ExitGameButton : public GameMenuButton {
    Q_OBJECT

public:
    explicit ExitGameButton(QWidget* parent = nullptr);

private slots:
    void handleClick();
};
