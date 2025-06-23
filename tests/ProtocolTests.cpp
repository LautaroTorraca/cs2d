#include "client/Protocol.h"
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "common/foo.h"
#include "server/GameParser.h"
#include "server/Protocol/Protocol.h"

using ::testing::HasSubstr;
using ::testing::ThrowsMessage;
using ::testing::AllOf;


namespace {
    TEST(CreateLobbyTest, Check) {
        Protocol protocol("8080");
        Client::Protocol clientProtocol("localhost", "8080");
        clientProtocol.createLobby({"hola", MapType::DUST, 2, 4});
        std::unique_ptr<Order> order = protocol.getNextOrder();
        ServerLobbyOrder& lobbyOrder = dynamic_cast<ServerLobbyOrder &>(*order);
        bool result = lobbyOrder.getOrderType() == LOBBY_CREATE &&
            lobbyOrder.getClientId() == 0 &&
            lobbyOrder.getGameName() == "hola" &&
            lobbyOrder.getRoundCount() == 4 &&
            lobbyOrder.getPlayerCount() == 2;
        protocol.end();
        std::unique_ptr<Order> exitOrder = protocol.getNextOrder();
        protocol.disconnect({0});
        EXPECT_EQ(result, true);
    }
    TEST(ListGamesTest, Check) {
        Protocol protocol("8080");
        Client::Protocol clientProtocol("localhost", "8080");
        clientProtocol.createLobby({"hola", MapType::DUST, 2, 4});
        std::unique_ptr<Order> order = protocol.getNextOrder();
        ServerLobbyOrder& lobbyOrder = dynamic_cast<ServerLobbyOrder &>(*order);
        std::vector<std::string> games;
        games.push_back(lobbyOrder.getGameName());
        std::vector<GameLobbyDTO> lobbies;
        lobbies.push_back(GameLobbyDTO("Partida", 2, MapType::DUST,  4));
        GamesListDTO gamesList(0, lobbies);
        protocol.sendGamesList(gamesList);
        GamesList list = clientProtocol.getGamesList();
        std::unique_ptr<Order> listRawOrder = protocol.getNextOrder();
        ServerLobbyOrder& listOrder = dynamic_cast<ServerLobbyOrder &>(*listRawOrder);
        bool result = listOrder.getOrderType() == LOBBY_LIST &&
            listOrder.getClientId() == 0;
        result = result && list.gamesLobbies.size() == 1 && list.gamesLobbies.at(0).gameName == lobbyOrder.getGameName();
        result = result && list.gamesLobbies.at(0).rounds == lobbyOrder.getRoundCount() && list.gamesLobbies.at(0).mapType == lobbyOrder.getMapType();
        protocol.end();
        std::unique_ptr<Order> exitOrder = protocol.getNextOrder();
        protocol.disconnect({0});
        EXPECT_EQ(result, true);
    }
    TEST(JoinGameTest, Check) {
        Protocol protocol("8080");
        Client::Protocol clientProtocol("localhost", "8080");
        clientProtocol.joinLobby({"hola", MapType::DUST, 2, 4});
        std::unique_ptr<Order> order = protocol.getNextOrder();
        ServerLobbyOrder& lobbyOrder = dynamic_cast<ServerLobbyOrder &>(*order);
        bool result = lobbyOrder.getOrderType() == LOBBY_JOIN &&
            lobbyOrder.getClientId() == 0 &&
                lobbyOrder.getGameName() == "hola";
        LobbyConnectionDTO lobbyConnection(lobbyOrder.getClientId(), ConnectionStatus::SUCCESS);
        protocol.sendLobbyConnectionStatus(lobbyConnection);
        LobbyConnectionDTO connectionStatus = clientProtocol.getLobbyConnection();
        result = result && connectionStatus.status == ConnectionStatus::SUCCESS;
        protocol.end();
        std::unique_ptr<Order> exitOrder = protocol.getNextOrder();
        protocol.disconnect({0});
        EXPECT_EQ(result, true);
    }
    TEST(LeaveLobbyTest, Check) {
        Protocol protocol("8080");
        Client::Protocol clientProtocol("localhost", "8080");
        clientProtocol.leaveLobby();
        std::unique_ptr<Order> order = protocol.getNextOrder();
        ServerLobbyOrder& lobbyOrder = dynamic_cast<ServerLobbyOrder &>(*order);
        bool result = lobbyOrder.getOrderType() == LOBBY_DISCONNECT &&  lobbyOrder.getClientId() == 0;
        protocol.end();
        std::unique_ptr<Order> exitOrder = protocol.getNextOrder();
        protocol.disconnect({0});
        EXPECT_EQ(result, true);
    }
    TEST(ReadyTest, Check) {
        Protocol protocol("8080");
        Client::Protocol clientProtocol("localhost", "8080");
        clientProtocol.ready({"Zoro", Team::COUNTER_TERRORISTS, Skin::GERMAN_GSG9});
        std::unique_ptr<Order> order = protocol.getNextOrder();
        GameLobbyOrder& gameLobbyOrder = dynamic_cast<GameLobbyOrder &>(*order);
        bool result = gameLobbyOrder.getOrderType() == GAME_LOBBY_READY &&  gameLobbyOrder.getPlayerId() == 0 &&
            gameLobbyOrder.getPlayerName() == "Zoro" && gameLobbyOrder.getTeamId() == Team::COUNTER_TERRORISTS &&
                gameLobbyOrder.getSkinId() == Skin::GERMAN_GSG9;
        protocol.end();
        std::unique_ptr<Order> exitOrder = protocol.getNextOrder();
        protocol.disconnect({0});
        EXPECT_EQ(result, true);
    }
    TEST(GetGameLobbyTest, Check) {
        Protocol protocol("8080");
        Client::Protocol clientProtocol("localhost", "8080");
        clientProtocol.ready({"Zoro", Team::COUNTER_TERRORISTS, Skin::GERMAN_GSG9});
        std::unique_ptr<Order> order = protocol.getNextOrder();
        GameLobbyOrder& gameLobbyOrder = dynamic_cast<GameLobbyOrder &>(*order);
        std::vector<PlayerChoicesDTO> playersChoices;
        playersChoices.push_back({gameLobbyOrder.getPlayerId(),
            gameLobbyOrder.getPlayerName(),
            gameLobbyOrder.getTeamId(),
            gameLobbyOrder.getSkinId()});
        protocol.sendLobby({GameLobbyStatus::SELECTING_STATUS, playersChoices, "hola", 4, MapType::DUST});
        GameLobbyDTO gameLobbyInfo = clientProtocol.getGameLobby();
        bool result = gameLobbyInfo.status == GameLobbyStatus::SELECTING_STATUS &&
            gameLobbyInfo.playersChoices.size() == playersChoices.size() &&
                gameLobbyInfo.playersChoices.at(0).id == playersChoices.at(0).id &&
                    gameLobbyInfo.playersChoices.at(0).playerName == playersChoices.at(0).playerName &&
                        gameLobbyInfo.playersChoices.at(0).team == playersChoices.at(0).team &&
                        gameLobbyInfo.playersChoices.at(0).skin == playersChoices.at(0).skin &&
                            gameLobbyInfo.mapType == MapType::DUST && gameLobbyInfo.gameName == "hola" &&
                                gameLobbyInfo.rounds == 4;
        protocol.end();
        std::unique_ptr<Order> exitOrder = protocol.getNextOrder();
        protocol.disconnect({0});
        EXPECT_EQ(result, true);
    }
    TEST(InGameMoveTest, Check) {
        Protocol protocol("8080");
        Client::Protocol clientProtocol("localhost", "8080");
        clientProtocol.move({Direction::Up});
        std::unique_ptr<Order> order = protocol.getNextOrder();
        InGameOrder& inGameOrder = dynamic_cast<InGameOrder &>(*order);
        bool result = inGameOrder.getOrderType() == IN_GAME_MOVE &&  inGameOrder.getPlayerId() == 0 &&
            inGameOrder.getDirection() == Movement::UP;
        protocol.end();
        std::unique_ptr<Order> exitOrder = protocol.getNextOrder();
        protocol.disconnect({0});
        EXPECT_EQ(result, true);
    }
    TEST(InGameAttackTest, Check) {
        Protocol protocol("8080");
        Client::Protocol clientProtocol("localhost", "8080");
        clientProtocol.attack();
        std::unique_ptr<Order> order = protocol.getNextOrder();
        InGameOrder& inGameOrder = dynamic_cast<InGameOrder &>(*order);
        bool result = inGameOrder.getOrderType() == IN_GAME_SHOOT &&  inGameOrder.getPlayerId() == 0;
        protocol.end();
        std::unique_ptr<Order> exitOrder = protocol.getNextOrder();
        protocol.disconnect({0});
        EXPECT_EQ(result, true);
    }
    TEST(InGamePickDropTest, Check) {
        Protocol protocol("8080");
        Client::Protocol clientProtocol("localhost", "8080");
        clientProtocol.pickUp();
        std::unique_ptr<Order> order = protocol.getNextOrder();
        InGameOrder& inGameOrder = dynamic_cast<InGameOrder &>(*order);
        bool result = inGameOrder.getOrderType() == IN_GAME_PICK_UP_ITEM &&  inGameOrder.getPlayerId() == 0;
        protocol.end();
        std::unique_ptr<Order> exitOrder = protocol.getNextOrder();
        protocol.disconnect({0});
        EXPECT_EQ(result, true);
    }
    TEST(InGameBuyTest, Check) {
        Protocol protocol("8080");
        Client::Protocol clientProtocol("localhost", "8080");
        clientProtocol.buy({ProductType::AK_47_WEAPON, 1});
        std::unique_ptr<Order> order = protocol.getNextOrder();
        InGameOrder& inGameOrder = dynamic_cast<InGameOrder &>(*order);
        bool result = inGameOrder.getOrderType() == IN_GAME_BUY &&  inGameOrder.getPlayerId() == 0 &&
            inGameOrder.getProduct() == ProductType::AK_47_WEAPON && inGameOrder.getAmount() == 1;
        protocol.end();
        std::unique_ptr<Order> exitOrder = protocol.getNextOrder();
        protocol.disconnect({0});
        EXPECT_EQ(result, true);
    }
    TEST(InGameChangeAngleTest, Check) {
        Protocol protocol("8080");
        Client::Protocol clientProtocol("localhost", "8080");
        clientProtocol.changeAngle(90);
        std::unique_ptr<Order> order = protocol.getNextOrder();
        InGameOrder& inGameOrder = dynamic_cast<InGameOrder &>(*order);
        bool result = inGameOrder.getOrderType() == IN_GAME_CHANGE_ANGLE &&  inGameOrder.getPlayerId() == 0 &&
            inGameOrder.getAngle() == 90;
        protocol.end();
        std::unique_ptr<Order> exitOrder = protocol.getNextOrder();
        protocol.disconnect({0});
        EXPECT_EQ(result, true);
    }
    TEST(InGameChangeWeaponTest, Check) {
        Protocol protocol("8080");
        Client::Protocol clientProtocol("localhost", "8080");
        clientProtocol.changeWeapon({0});
        std::unique_ptr<Order> order = protocol.getNextOrder();
        InGameOrder& inGameOrder = dynamic_cast<InGameOrder &>(*order);
        bool result = inGameOrder.getOrderType() == IN_GAME_SWITCH_WEAPON &&  inGameOrder.getPlayerId() == 0 &&
            inGameOrder.getWeaponInformation() == 0;
        protocol.end();
        std::unique_ptr<Order> exitOrder = protocol.getNextOrder();
        protocol.disconnect({0});
        EXPECT_EQ(result, true);
    }
    TEST(InGamePlantBombTest, Check) {
        Protocol protocol("8080");
        Client::Protocol clientProtocol("localhost", "8080");
        clientProtocol.plantBomb();
        std::unique_ptr<Order> order = protocol.getNextOrder();
        InGameOrder& inGameOrder = dynamic_cast<InGameOrder &>(*order);
        bool result = inGameOrder.getOrderType() == IN_GAME_PLANT_BOMB &&  inGameOrder.getPlayerId() == 0;
        protocol.end();
        std::unique_ptr<Order> exitOrder = protocol.getNextOrder();
        protocol.disconnect({0});
        EXPECT_EQ(result, true);
    }
    TEST(InGameDefuseBombTest, Check) {
        Protocol protocol("8080");
        Client::Protocol clientProtocol("localhost", "8080");
        clientProtocol.defuseBomb();
        std::unique_ptr<Order> order = protocol.getNextOrder();
        InGameOrder& inGameOrder = dynamic_cast<InGameOrder &>(*order);
        bool result = inGameOrder.getOrderType() == IN_GAME_DEFUSE_BOMB &&  inGameOrder.getPlayerId() == 0;
        protocol.end();
        std::unique_ptr<Order> exitOrder = protocol.getNextOrder();
        protocol.disconnect({0});
        EXPECT_EQ(result, true);
    }
    TEST(InGameExitTest, Check) {
        Protocol protocol("8080");
        Client::Protocol clientProtocol("localhost", "8080");
        clientProtocol.exit();
        std::unique_ptr<Order> order = protocol.getNextOrder();
        InGameOrder& inGameOrder = dynamic_cast<InGameOrder &>(*order);
        bool result = inGameOrder.getOrderType() == IN_GAME_EXIT &&  inGameOrder.getPlayerId() == 0;
        protocol.end();
        protocol.disconnect({0});
        EXPECT_EQ(result, true);
    }
TEST(InGameReadPreSnapshotTest, Check)
    {
        Protocol protocol("8080");
        Client::Protocol clientProtocol("localhost", "8080");
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        std::vector<std::vector<uint8_t>> map = { {1, 1, 1},
                                                  {2, 2, 2}};
        std::map<ProductType, double> prices;
        prices.emplace(ProductType::AK_47_WEAPON, 500);
        protocol.sendPreSnapshot({0, map, prices});
        PreSnapshot preSnapshot = clientProtocol.receivePreSnapshot();
        bool result = preSnapshot.clientId == 0 && preSnapshot.map.size() == 2 &&
            preSnapshot.map.at(0).at(0) == 1 && preSnapshot.map.at(0).at(1) == 1 &&
                preSnapshot.map.at(0).at(2) == 1 && preSnapshot.map.at(1).at(0) == 2 &&
                    preSnapshot.map.at(1).at(1) == 2 && preSnapshot.map.at(1).at(2) == 2 &&
                        preSnapshot.shopInfo.size() == 1 && preSnapshot.shopInfo.at(AK_47_WEAPON) == 500;
        EXPECT_EQ(result, true);
    }
    TEST(InGameReadSnapshotTest, Check) {
        Protocol protocol("8080");
        Client::Protocol clientProtocol("localhost", "8080");
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        std::vector<PlayerInfoDTO> playersInfo;
        std::vector<WeaponInfoDTO> weaponsInfo;
        std::vector<ProjectileDTO> projectilesInfo;
        ProjectileDTO projectile({ 100, 100 });
        projectilesInfo.push_back(projectile);
        weaponsInfo.push_back({30, WeaponType::GLOCK, projectilesInfo});
        WeaponInfoDTO actualWeapon(30, WeaponType::GLOCK);
        playersInfo.push_back({0, "Zoro", Skin::GERMAN_GSG9, {280, 112}, 90, 500, 100, weaponsInfo, actualWeapon, 0, 0, PlayerStatus::LIVING, 500});
        std::vector<DropDTO> dropsInfo;
        WeaponInfoDTO droppedWeapon(30, WeaponType::AK47);
        dropsInfo.push_back({droppedWeapon, {48, 48}});
        GameInfoDTO gameInfo(GameStatus::ON_GOING, 4, 0, 0, playersInfo, dropsInfo, {298, 196}, 10, 10, 10);
        protocol.sendSnapshot(gameInfo);
        Snapshot snapshot = clientProtocol.receiveSnapshot();
        std::vector<PlayerInformation> playersInformation = snapshot.playersInfo;
        bool result = snapshot.status == gameInfo.getStatus() && snapshot.currentRound == gameInfo.getCurrentRound() &&
            snapshot.countersWinsRounds == gameInfo.getCountersWinsRounds() &&
                snapshot.terroristsWinsRounds == gameInfo.getTerroristsWinsRounds() &&
                playersInformation.size() == gameInfo.getPlayersInfo().size() &&
                    playersInformation.at(0).id == gameInfo.getPlayersInfo().at(0).getId() &&
                        playersInformation.at(0).skin == gameInfo.getPlayersInfo().at(0).getSkin() &&
                            playersInformation.at(0).name == gameInfo.getPlayersInfo().at(0).getName() &&
                                playersInformation.at(0).position.x == gameInfo.getPlayersInfo().at(0).getCoordinate().getX() &&
                                    playersInformation.at(0).position.y == gameInfo.getPlayersInfo().at(0).getCoordinate().getY() &&
                                        playersInformation.at(0).angle == gameInfo.getPlayersInfo().at(0).getAngle() &&
                                            playersInformation.at(0).actualMoney == gameInfo.getPlayersInfo().at(0).getMoney() &&
                                                playersInformation.at(0).actualHealthPoints == gameInfo.getPlayersInfo().at(0).getHealth() &&
                                                    playersInformation.at(0).weaponsInfo.size() == gameInfo.getPlayersInfo().at(0).getWeaponsInfo().size() &&
                                                        playersInformation.at(0).weaponsInfo.at(0).ammoAmount == gameInfo.getPlayersInfo().at(0).getWeaponsInfo().at(0).getAmmoAmount() &&
                                                            playersInformation.at(0).weaponsInfo.at(0).weaponType == gameInfo.getPlayersInfo().at(0).getWeaponsInfo().at(0).getWeaponType() &&
                                                                playersInformation.at(0).weaponsInfo.at(0).projectilesInfo.size() == gameInfo.getPlayersInfo().at(0).getWeaponsInfo().at(0).getProjectilesInfo().size() &&
                                                                    playersInformation.at(0).weaponsInfo.at(0).projectilesInfo.at(0).projectilePosition.x == gameInfo.getPlayersInfo().at(0).getWeaponsInfo().at(0).getProjectilesInfo().at(0).getCoordinateDTO().getX() &&
                                                                        playersInformation.at(0).weaponsInfo.at(0).projectilesInfo.at(0).projectilePosition.y == gameInfo.getPlayersInfo().at(0).getWeaponsInfo().at(0).getProjectilesInfo().at(0).getCoordinateDTO().getY() &&
                                                                            playersInformation.at(0).actualWeapon.ammoAmount == gameInfo.getPlayersInfo().at(0).getActualWeapon().getAmmoAmount() &&
                                                                                playersInformation.at(0).actualWeapon.weaponType == gameInfo.getPlayersInfo().at(0).getActualWeapon().getWeaponType() &&
                                                                                    playersInformation.at(0).actualWeapon.projectilesInfo.size() == gameInfo.getPlayersInfo().at(0).getActualWeapon().getProjectilesInfo().size() &&
                                                                                             playersInformation.at(0).kills == gameInfo.getPlayersInfo().at(0).getKills() &&
                                                                                                 playersInformation.at(0).deaths == gameInfo.getPlayersInfo().at(0).getDeaths() &&
                                                                                                 playersInformation.at(0).status == gameInfo.getPlayersInfo().at(0).getStatus() &&
                                                                                                    snapshot.dropsInfo.size() == gameInfo.getDropsInfo().size() &&
                                                                                                        snapshot.dropsInfo.at(0).position.x == gameInfo.getDropsInfo().at(0).getPosition().getX() &&
                                                                                                            snapshot.dropsInfo.at(0).position.y == gameInfo.getDropsInfo().at(0).getPosition().getY() &&
                                                                                                                snapshot.dropsInfo.at(0).weapon.ammoAmount == gameInfo.getDropsInfo().at(0).getDropInfo().getAmmoAmount() &&
                                                                                                                    snapshot.dropsInfo.at(0).weapon.projectilesInfo.size() == gameInfo.getDropsInfo().at(0).getDropInfo().getProjectilesInfo().size() &&
                                                                                                                        snapshot.dropsInfo.at(0).weapon.weaponType == gameInfo.getDropsInfo().at(0).getDropInfo().getWeaponType() &&
                                                                                                                            snapshot.plantedBombPosition.x == gameInfo.getPlantedBombPosition().getX() &&
                                                                                                                                snapshot.plantedBombPosition.y == gameInfo.getPlantedBombPosition().getY() &&
                                                                                                                                    snapshot.bombTimer == gameInfo.getBombTimer() &&
                                                                                                                                    snapshot.actualTime == gameInfo.getElapsedTime() &&
                                                                                                                                        snapshot.totalRounds == gameInfo.getRounds();
        EXPECT_EQ(result, true);
    }
}