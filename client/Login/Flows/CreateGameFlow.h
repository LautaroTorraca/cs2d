#pragma once
#include "GameFlowBase.h"
using namespace Client;

class CreateGameFlow : public GameFlowBase {
public:
    CreateGameFlow(QLineEdit* usernameInput, Protocol& protocol, QWidget* parent);
    void run();
};

