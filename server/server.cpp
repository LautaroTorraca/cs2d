#include "server.h"

#include "Ui.h"

Server::Server(const std::string& port) :
              protocol(port),
              inGameServer(protocol, [&] (const size_t& id) {this->serverLobby.erase(id);}),
              gameLobbyServer(inGameServer, protocol , [&] (const size_t& id) {this->serverLobby.erase(id);}),
              serverLobby(protocol, this->gameLobbyServer) {

    setupLobbyOrders();
    setupGameLobbyOrders();
    setupInGameOrders();
}

void Server::setupLobbyOrders() {
    orderTranslator[LOBBY_CREATE] = [this](const std::unique_ptr<Order>& order) {
        serverLobby.handle(order);
    };

    orderTranslator[LOBBY_LIST] = [this](const std::unique_ptr<Order>& order) {
        serverLobby.handle(order);
    };

    orderTranslator[LOBBY_JOIN] = [this](const std::unique_ptr<Order>& order) {
        serverLobby.handle(order);
    };

    orderTranslator[LOBBY_DISCONNECT] = [this](const std::unique_ptr<Order>& order) {
        serverLobby.handle(order);
    };
}

void Server::setupGameLobbyOrders() {
    orderTranslator[GAME_LOBBY_READY] = [this](const std::unique_ptr<Order>& order) {
        gameLobbyServer.handle(order);
    };

    orderTranslator[GAME_LOBBY_EXIT] = [this](const std::unique_ptr<Order>& order) {
        gameLobbyServer.handle(order);
    };
}

void Server::setupInGameOrders() {
    orderTranslator[IN_GAME_MOVE] = [this](const std::unique_ptr<Order>& order) {
        inGameServer.handle(order);
    };

    orderTranslator[IN_GAME_SHOOT] = [this](const std::unique_ptr<Order>& order) {
        inGameServer.handle(order);
    };

    orderTranslator[IN_GAME_PICK_UP_ITEM] = [this](const std::unique_ptr<Order>& order) {
        inGameServer.handle(order);
    };

    orderTranslator[IN_GAME_DROP_ITEM] = [this](const std::unique_ptr<Order>& order) {
        inGameServer.handle(order);
    };

    orderTranslator[IN_GAME_BUY] = [this](const std::unique_ptr<Order>& order) {
        inGameServer.handle(order);
    };

    orderTranslator[IN_GAME_CHANGE_ANGLE] = [this](const std::unique_ptr<Order>& order) {
        inGameServer.handle(order);
    };

    orderTranslator[IN_GAME_SWITCH_WEAPON] = [this](const std::unique_ptr<Order>& order) {
        inGameServer.handle(order);
    };

    orderTranslator[IN_GAME_PLANT_BOMB] = [this](const std::unique_ptr<Order>& order) {
        inGameServer.handle(order);
    };

    orderTranslator[IN_GAME_DEFUSE_BOMB] = [this](const std::unique_ptr<Order>& order) {
        inGameServer.handle(order);
    };

    orderTranslator[IN_GAME_EXIT] = [this](const std::unique_ptr<Order>& order) {
        inGameServer.handle(order);
    };
}

void Server::run() {
    Ui ui( this->protocol);
    ui.start();
    while (true) {
        try {
            std::unique_ptr<Order> order = protocol.getNextOrder();

            OrderType type = order->getOrderType();


            if (!orderTranslator.contains(type)) {
                continue;
            }

            orderTranslator.at(type)(order);
        } catch (std::exception& e) {
            std::cout << "Main server: " << e.what() << std::endl;
            break;
        }
    }
    ui.join();
}
