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

    this->serviceStopped = true;
    std::cout << "Ui::run. serviceStopped." << std::endl;
    try {
        this->protocol.stopService();
    } catch (ClosedQueue&) {
        std::cerr << "Ui: >><< Closed queue" << std::endl;
    }
}