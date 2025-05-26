#include "ClientHandler.h"

#include "OpCodesConstans.h"

ClientHandler::ClientHandler(Socket& socket, const size_t& clientId, Queue<std::shared_ptr<Request>>& requestQueue)
    :   userSocket(socket), id(clientId),
        requestsQueue(requestQueue),
        lobbyHandler(userSocket, clientId),
        gameLobbyHandler(userSocket, clientId),
        inGameHandler(userSocket, clientId) {

    registerOpcodes();
}

void ClientHandler::registerOpcodes() {
    opcodeDispatcher[OPCODE_CREATE_GAME] = [&]() { return lobbyHandler.handle(OPCODE_CREATE_GAME); };
    opcodeDispatcher[OPCODE_JOIN_GAME] = [&]() { return lobbyHandler.handle(OPCODE_JOIN_GAME); };
    opcodeDispatcher[OPCODE_LIST_GAMES] = [&]() { return lobbyHandler.handle(OPCODE_LIST_GAMES); };
    opcodeDispatcher[OPCODE_DISCONNECT] = [&]() { return lobbyHandler.handle(OPCODE_DISCONNECT); };

    opcodeDispatcher[OPCODE_READY] = [&]() { return gameLobbyHandler.handle(OPCODE_READY); };
    opcodeDispatcher[OPCODE_EXIT_LOBBY] = [&]() { return gameLobbyHandler.handle(OPCODE_EXIT_LOBBY); };

    opcodeDispatcher[OPCODE_PLAYER_MOVEMENT] = [&]() { return inGameHandler.handle(OPCODE_PLAYER_MOVEMENT); };
    opcodeDispatcher[OPCODE_SHOOT] = [&]() { return inGameHandler.handle(OPCODE_SHOOT); };
    opcodeDispatcher[OPCODE_BUY_AMMO] = [&]() { return inGameHandler.handle(OPCODE_BUY_AMMO); };
    opcodeDispatcher[OPCODE_BUY_WEAPON] = [&]() { return inGameHandler.handle(OPCODE_BUY_WEAPON); };
    opcodeDispatcher[OPCODE_PICK_UP_ITEM] = [&]() { return inGameHandler.handle(OPCODE_PICK_UP_ITEM); };
    opcodeDispatcher[OPCODE_DROP_ITEM] = [&]() { return inGameHandler.handle(OPCODE_DROP_ITEM); };
    opcodeDispatcher[OPCODE_SWITCH_WEAPON] = [&]() { return inGameHandler.handle(OPCODE_SWITCH_WEAPON); };
    opcodeDispatcher[OPCODE_PLANT_BOMB] = [&]() { return inGameHandler.handle(OPCODE_PLANT_BOMB); };
    opcodeDispatcher[OPCODE_DEFUSE_BOMB] = [&]() { return inGameHandler.handle(OPCODE_DEFUSE_BOMB); };
    opcodeDispatcher[OPCODE_EXIT_GAME] = [&]() { return inGameHandler.handle(OPCODE_JOIN_GAME); };
}


void ClientHandler::run() {
    try {
        while (true) {
            uint8_t opCode;
            userSocket.recvall(&opCode, sizeof(opCode));

            if (!opcodeDispatcher.contains(opCode)) {
                throw std::runtime_error("OpCode no soportado: " + std::to_string(opCode));
            }

            Request request = opcodeDispatcher.at(opCode)();

            requestsQueue.push(std::make_shared<Request>(std::move(request)));
        }
    } catch (...) {
        // TODO
    }
}

ClientHandler::~ClientHandler() {
    this->userSocket.close();
}
