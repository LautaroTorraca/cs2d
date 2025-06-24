#pragma once

#include "GameFlowBase.h"

class ListGameFlow : public GameFlowBase {
public:
    ListGameFlow(QLineEdit* usernameInput, Protocol& protocol, QWidget* parent, ServerMenu* menu);
    void run();
};
