#pragma once

#include "GameFlowBase.h"

using namespace Client;

class ListGameFlow : public GameFlowBase {
public:
    ListGameFlow(QLineEdit* usernameInput, Protocol& protocol, QWidget* parent);
    void run();
};
