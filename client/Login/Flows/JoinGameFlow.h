#pragma once
#include "GameFlowBase.h"

class JoinGameFlow : public GameFlowBase {
public:
    JoinGameFlow(QLineEdit* usernameInput, Protocol& protocol, QWidget* parent);
    void run();
};
