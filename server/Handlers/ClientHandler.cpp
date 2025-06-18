#include "ClientHandler.h"

#include <iostream>
#include <sstream>
#include <string>

#include "Constants/OpCodesConstans.h"

#include "GameInfoDTO.h"

ClientHandler::ClientHandler(Socket& socket, const size_t& clientId,
                             Queue<std::shared_ptr<Request>>& requestQueue):
        userSocket(std::move(socket)),
        id(clientId),
        requestsQueue(requestQueue),
        lobbyHandler(userSocket, clientId),
        gameLobbyHandler(userSocket, clientId),
        inGameHandler(userSocket, clientId),
        sender(this->userSocket) {

    registerOpcodes();
}

void ClientHandler::registerOpcodes() {
    opcodeDispatcher[OPCODE_CREATE_GAME] = [&]() {
        return lobbyHandler.handle(OPCODE_CREATE_GAME);
    };
    opcodeDispatcher[OPCODE_JOIN_GAME] = [&]() { return lobbyHandler.handle(OPCODE_JOIN_GAME); };
    opcodeDispatcher[OPCODE_LIST_GAMES] = [&]() { return lobbyHandler.handle(OPCODE_LIST_GAMES); };
    opcodeDispatcher[OPCODE_DISCONNECT] = [&]() { return lobbyHandler.handle(OPCODE_DISCONNECT); };

    opcodeDispatcher[OPCODE_READY] = [this]() { return this->gameLobbyHandler.handle(OPCODE_READY); };
    opcodeDispatcher[OPCODE_EXIT_LOBBY] = [&]() {
        return gameLobbyHandler.handle(OPCODE_EXIT_LOBBY);
    };

    opcodeDispatcher[OPCODE_PLAYER_MOVEMENT] = [&]() {
        return inGameHandler.handle(OPCODE_PLAYER_MOVEMENT);
    };
    opcodeDispatcher[OPCODE_SHOOT] = [&]() { return inGameHandler.handle(OPCODE_SHOOT); };
    opcodeDispatcher[OPCODE_BUY] = [&]() { return inGameHandler.handle(OPCODE_BUY); };
    opcodeDispatcher[OPCODE_CHANGE_ANGLE] = [&]() {
        return inGameHandler.handle(OPCODE_CHANGE_ANGLE);
    };
    opcodeDispatcher[OPCODE_PICK_UP_ITEM] = [&]() {
        return inGameHandler.handle(OPCODE_PICK_UP_ITEM);
    };
    opcodeDispatcher[OPCODE_DROP_ITEM] = [&]() { return inGameHandler.handle(OPCODE_DROP_ITEM); };
    opcodeDispatcher[OPCODE_SWITCH_WEAPON] = [&]() {
        return inGameHandler.handle(OPCODE_SWITCH_WEAPON);
    };
    opcodeDispatcher[OPCODE_PLANT_BOMB] = [&]() { return inGameHandler.handle(OPCODE_PLANT_BOMB); };
    opcodeDispatcher[OPCODE_DEFUSE_BOMB] = [&]() {
        return inGameHandler.handle(OPCODE_DEFUSE_BOMB);
    };
    opcodeDispatcher[OPCODE_EXIT_GAME] = [&]() { return inGameHandler.handle(OPCODE_JOIN_GAME); };
}


void ClientHandler::run() {

    while (this->should_keep_running()) {
        try {
            uint8_t opCode;
            this->userSocket.recvall(&opCode, sizeof(opCode));

            //std::cout << "ClientHandler::run, opecode: " << std::to_string(opCode) << std::endl;
            if (!this->opcodeDispatcher.contains(opCode)) {
                throw std::runtime_error("OpCode no soportado: " + std::to_string(opCode));
            }

            Request request = this->opcodeDispatcher.at(opCode)();

            this->requestsQueue.push(std::make_shared<Request>(std::move(request)));
        } catch (std::exception& e) {
            std::cout << "Client disconnected. error: " << e.what() << std::endl;
            this->stop();
        }
    }
}


void ClientHandler::sendSnapshot(const GameInfoDTO& gameInfo) {
    for (auto& playerInfo: gameInfo.getPlayersInfo()) {
        this->sender.send(NEW);
        this->sender.send(playerInfo);
    }
    this->sender.send(STOP);
    uint8_t status = gameInfo.getStatus();
    this->sender.send(gameInfo.getCurrentRound());
    this->sender.send(gameInfo.getCountersWinsRounds());
    this->sender.send(gameInfo.getTerroristsWinsRounds());
    this->sender.send(gameInfo.getPlantedBombPosition());
    this->sender.send(status);
    for (auto& drop: gameInfo.getDropsInfo()) {
        this->sender.send(NEW);
        this->sender.send(drop);
    }
    this->sender.send(STOP);
}

void ClientHandler::sendPreSnapshot(const PreSnapshot& preSnapshot) {
    this->sender.send(preSnapshot.clientId);
    this->sender.send(preSnapshot.map);
}

void ClientHandler::stopService() { this->userSocket.close(); }

void ClientHandler::sendGamesList(const std::vector<std::string>& gamesList) {
    std::stringstream gamesListStream;
    for (const auto& game: gamesList) {
        gamesListStream << game << "\n";
    }
    std::string gamesListString = gamesListStream.str();
    uint16_t size = gamesListString.size();
    this->userSocket.sendall(&size, sizeof(size));
    this->userSocket.sendall(gamesList.data(), gamesList.size());
}

void ClientHandler::sendGameLobby(const GameLobbyDTO& gameLobbyInfo) {
    std::vector<PlayerChoicesDTO> playersChoices = gameLobbyInfo.playersChoices;
    uint8_t status = gameLobbyInfo.status;
    uint8_t mapType = static_cast<uint8_t>(gameLobbyInfo.mapType);
    this->sender.send(status);
    for (const auto &playerChoice : playersChoices) {
        uint8_t skin = playerChoice.skin;
        uint8_t team = playerChoice.team;
        this->sender.send(NEW);
        this->sender.send(playerChoice.id);
        this->sender.send(playerChoice.playerName);
        this->sender.send(team);
        this->sender.send(skin);
    }
    this->sender.send(STOP);
    this->sender.send(gameLobbyInfo.gameName);
    this->sender.send(gameLobbyInfo.rounds);
    this->sender.send(mapType);

}

void ClientHandler::sendLobbyConnectonStatus(const LobbyConnectionDTO& lobbyConnection) {
    uint8_t lobbyConnectionStatus = lobbyConnection.status;
    this->sender.send(this->id);
    this->sender.send(lobbyConnectionStatus);
}

ClientHandler::~ClientHandler() { this->stopService(); }
