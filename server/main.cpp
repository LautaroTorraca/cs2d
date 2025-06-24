#include <iostream>

#include "server.h"

#define PORT 1
#define RIGHT_ARGUMENTS_AMOUNT 2
#define BAD_ARGUMENTS_AMOUNT "The server needs more arguments."
#define FAIL -1
#define SUCCESS 0

int main(int argc, char** argv) {
    try {
        if (argc != RIGHT_ARGUMENTS_AMOUNT) {
            std::cerr << BAD_ARGUMENTS_AMOUNT << std::endl;
            return FAIL;
        }

        const std::string port = argv[PORT];
        Server server(port);
        server.run();

    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
        return FAIL;
    }
    return SUCCESS;
}
