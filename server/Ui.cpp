//
// Created by lionel on 16/06/25.
//

#include "Ui.h"
#define EXIT_COMMAND "q"
void Ui::run() {
    std::string command;
    while (command != EXIT_COMMAND) {
        std::cin >> command;
    }
    try {
        this->protocol.end();
    } catch (ClosedQueue&) {
    }
}