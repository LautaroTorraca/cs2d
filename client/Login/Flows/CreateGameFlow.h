#pragma once
#include "GameFlowBase.h"

class CreateGameFlow : public GameFlowBase {
public:
    CreateGameFlow(QLineEdit* usernameInput, Protocol& protocol, QWidget* parent);
    void run();
};

