#include <exception>
#include <iostream>

#include <SDL2/SDL.h>

#include "GameClient.h"

using namespace DTO;


int main(int argc, char* argv[]) {
    try {

        GameClient game(argv[1]);
        game.run(argc, argv);
        return 0;

    } catch (std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
}
