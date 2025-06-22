#include "ClientHandler.h"

#include <iostream>
#include <sstream>
#include <string>

#include <sys/socket.h>

#include "server/Constants/OpCodesConstans.h"

#include "server/GameInfoDTO.h"
#include "server/Constants/KeyContants.h"
#include "liberror.h"

ClientHandler::ClientHandler(Socket& socket, const size_t& clientId,
                             Queue<std::shared_ptr<Request>>& requestQueue):
        userSocket(std::move(socket)),
        id(clientId),
        requestsQueue(requestQueue),
        lobbyHandler(userSocket, clientId),
        gameLobbyHandler(userSocket, clientId),
        inGameHandler(userSocket, clientId),
        reader(this->userSocket),
        sender(this->userSocket),
        status(IN_LOBBY),
        ended(false) {

    registerOpcodes();
    this->setDisconnectionFetcher();
}

void ClientHandler::setDisconnectionFetcher() {
    this->disconnectionFetcher[IN_LOBBY] = [&] () {
        std::map<std::string, std::vector<char>> message;
        message.emplace(opCodeKey, std::vector<char>(SINGLE_VALUE, OPCODE_DISCONNECT));
        this->requestsQueue.push(std::make_shared<Request>(this->id, message));
    };

    this->disconnectionFetcher[IN_GAME_LOBBY] = [&] () {
        std::map<std::string, std::vector<char>> message;
        message.emplace(opCodeKey, std::vector<char>(SINGLE_VALUE, OPCODE_EXIT_LOBBY));
        this->requestsQueue.push(std::make_shared<Request>(this->id, message));
    };

    this->disconnectionFetcher[IN_GAME] = [&] () {
        std::map<std::string, std::vector<char>> message;
        message.emplace(opCodeKey, std::vector<char>(SINGLE_VALUE, OPCODE_EXIT_GAME));
        this->requestsQueue.push(std::make_shared<Request>(this->id, message));
    };
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
    opcodeDispatcher[OPCODE_EXIT_GAME] = [&]() { return inGameHandler.handle(OPCODE_EXIT_GAME); };
}


void ClientHandler::run() {

    while (this->should_keep_running()) {
        try {
            uint8_t opCode = this->reader.u8tReader();

            //std::cout << "ClientHandler::run, opecode: " << std::to_string(opCode) << std::endl;
            if (!this->opcodeDispatcher.contains(opCode)) {
                throw std::runtime_error("OpCode no soportado: " + std::to_string(opCode));
            }

            Request request = this->opcodeDispatcher.at(opCode)();

            this->requestsQueue.push(std::make_shared<Request>(std::move(request)));
        } catch (std::exception& e) {
            this->stop();
            std::cout << "Client " << this->id << " disconnected. " << e.what() << std::endl;
        }
    }
    if (!this->ended)
        this->disconnectionFetcher.at(this->status)();
}


void ClientHandler::sendSnapshot(const GameInfoDTO& gameInfo) {
    for (auto& playerInfo: gameInfo.getPlayersInfo()) {
        this->sender.send(NEW);
        this->sender.send(playerInfo);
    }
    this->sender.send(STOP);
    uint8_t gameStatus = gameInfo.getStatus();
    this->sender.send(gameInfo.getCurrentRound());
    this->sender.send(gameInfo.getCountersWinsRounds());
    this->sender.send(gameInfo.getTerroristsWinsRounds());
    this->sender.send(gameInfo.getPlantedBombPosition());
    this->sender.send(gameInfo.getBombTimer());
    this->sender.send(gameStatus);
    for (auto& drop: gameInfo.getDropsInfo()) {
        this->sender.send(NEW);
        this->sender.send(drop);
    }
    this->sender.send(STOP);
    this->sender.send(gameInfo.getElapsedTime());
    this->sender.send(gameInfo.getRounds());
}

void ClientHandler::sendPreSnapshot(const PreSnapshot& preSnapshot) {
    this->sender.send(preSnapshot.clientId);
    this->sender.send(preSnapshot.map);
    this->sender.send(preSnapshot.shopInfo);
}

void ClientHandler::stopService() {
    try {
        this->stop();
        this->userSocket.shutdown(SHUT_RDWR);
    } catch (LibError&) {
        //LOGG Error
    }
}

void ClientHandler::endService() {
    this->ended = true;
    this->stopService();
}

void ClientHandler::sendGamesList(const std::vector<std::string>& gamesList) {
    std::stringstream gamesListStream;
    for (const auto& game: gamesList) {
        gamesListStream << game << "\n";
    }
    std::string gamesListString = gamesListStream.str();
    this->sender.send(gamesListString);
}

void ClientHandler::sendGameLobby(const GameLobbyDTO& gameLobbyInfo) {
    std::vector<PlayerChoicesDTO> playersChoices = gameLobbyInfo.playersChoices;
    uint8_t lobbyStatus = (uint8_t)gameLobbyInfo.status;
    uint8_t mapType = static_cast<uint8_t>(gameLobbyInfo.mapType);
    if (gameLobbyInfo.status == READY_STATUS) {
        this->status = IN_GAME;
    }
    this->sender.send(lobbyStatus);
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
    if (lobbyConnection.status == SUCCESS) {
        this->status = IN_GAME_LOBBY;
    }
    this->sender.send(this->id);
    this->sender.send(lobbyConnectionStatus);
}

ClientHandler::~ClientHandler() { }
