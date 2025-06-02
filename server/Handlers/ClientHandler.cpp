#include "ClientHandler.h"

#include <sstream>

#include "GameInfoDTO.h"
#include "OpCodesConstans.h"
#include "Sender.h"

ClientHandler::ClientHandler(Socket& socket, const size_t& clientId, Queue<std::shared_ptr<Request>>& requestQueue)
    :   userSocket(socket), id(clientId),
        requestsQueue(requestQueue),
        lobbyHandler(userSocket, clientId),
        gameLobbyHandler(userSocket, clientId),
        inGameHandler(userSocket, clientId),
        sender(this->userSocket){

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

        while (this->should_keep_running()) {
            try {
                uint8_t opCode;
                userSocket.recvall(&opCode, sizeof(opCode));

                if (!opcodeDispatcher.contains(opCode)) {
                    throw std::runtime_error("OpCode no soportado: " + std::to_string(opCode));
                }

                Request request = opcodeDispatcher.at(opCode)();

                requestsQueue.push(std::make_shared<Request>(std::move(request)));
            } catch (...) {
                this->stop();
            }
        }
}


void ClientHandler::sendSnapshot(const GameInfoDTO& gameInfo) {
    for (auto& playerInfo : gameInfo.getPlayersInfo()) {
        this->sender.send(playerInfo);
    }
    uint8_t status = gameInfo.getStatus();
    this->sender.send(gameInfo.getCurrentRound());
    this->sender.send(gameInfo.getCountersWinsRounds());
    this->sender.send(gameInfo.getTerroristsWinsRounds());
    this->sender.send(gameInfo.getPlantedBombPosition());
    this->sender.send(status);
    for ( auto& drop : gameInfo.getDropsInfo() ) {
        this->sender.send(drop);

    }

}

void ClientHandler::sendPreSnapshot(const PreSnapshot& preSnapshot) {
    this->sender.send(preSnapshot.clientId);
    this->sender.send(preSnapshot.map);
}

void ClientHandler::stopService() {
    this->userSocket.close();
}

void ClientHandler::sendGamesList(const std::vector<std::string> &gamesList) const {
    std::stringstream gamesListStream;
    for (const auto &game : gamesList) {
        gamesListStream << game << "\n";
    }
    std::string gamesListString = gamesListStream.str();
    uint16_t size = gamesListString.size();
    this->userSocket.sendall(&size, sizeof(size));
    this->userSocket.sendall(gamesList.data(), gamesList.size());
}

void ClientHandler::sendGameLobby(const GameLobbyDTO &gameLobbyInfo) {
    std::vector<PlayerChoicesDTO> playersChoices = gameLobbyInfo.playersChoices;
    for (const auto &playerChoice : playersChoices) {
        uint8_t skin = playerChoice.skin;
        uint8_t team = playerChoice.team;
        uint8_t status = gameLobbyInfo.status;
        this->sender.send(gameLobbyInfo.gameName);
        this->sender.send(gameLobbyInfo.rounds);
        this->sender.send(playerChoice.id);
        this->sender.send(playerChoice.playerName);
        this->sender.send(skin);
        this->sender.send(team);
        this->sender.send(status);
    }
}

void ClientHandler::sendLobbyConnectonStatus(const LobbyConnectionDTO &lobbyConnection) {
    uint8_t lobbyConnectionStatus = lobbyConnection.status;
    this->sender.send(lobbyConnectionStatus);
}

ClientHandler::~ClientHandler() {
    this->stopService();
}
