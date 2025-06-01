#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "server/ProductType.h"
#include "server/Game.h"
#include "server/GameParser.h"
#include "server/PlayerInfoDTO.h"
#include "server/WeaponConstants.h"

using ::testing::HasSubstr;
using ::testing::ThrowsMessage;
using ::testing::AllOf;


namespace {
    TEST(SpawnTest, Check) {
        GameParser parser("../maps/test_map.yaml", "../gameConstants/shop.yaml", "../gameConstants/WeaponsConfig.yaml");
        Game game(parser, 10);
        game.addPlayer(0, "juan", Team::COUNTER_TERRORISTS, SEAL_FORCE);
        std::vector<PlayerInfoDTO> playersInfo = game.getPlayersInfo();
        const PlayerInfoDTO& playerInfo = playersInfo.back();
        Coordinate expectedCoordinate(304, 144);
        Coordinate playerActualPosition(playerInfo.getCoordinate().getX(), playerInfo.getCoordinate().getY());
        EXPECT_EQ(expectedCoordinate, playerActualPosition);
    }
    TEST(MovementTest, Check) {
        GameParser parser("../maps/test_map.yaml", "../gameConstants/shop.yaml", "../gameConstants/WeaponsConfig.yaml");
        Game game(parser, 10);
        game.addPlayer(0, "juan", Team::COUNTER_TERRORISTS, SEAL_FORCE);
        game.addPlayer(1, "carlos", Team::TERRORISTS, PHOENIX);
        game.advance(30);
        Coordinate displacement(0, -4);
        game.move(0, displacement);
        std::vector<PlayerInfoDTO> playersInfo = game.getPlayersInfo();
        const PlayerInfoDTO& playerInfo = playersInfo.at(0);
        Coordinate actualPosition( playerInfo.getCoordinate().getX(),playerInfo.getCoordinate().getY());
        Coordinate expectedPosition(304,140);
        EXPECT_EQ(actualPosition, expectedPosition);
    }
    TEST(CollisionTest, Check) {
        GameParser parser("../maps/test_map.yaml", "../gameConstants/shop.yaml", "../gameConstants/WeaponsConfig.yaml");
        Game game(parser, 10);
        game.addPlayer(0, "juan", Team::COUNTER_TERRORISTS, SEAL_FORCE);//juan esta en (304, 144)
        game.addPlayer(1, "carlos", Team::TERRORISTS, PHOENIX);//carlos esta en (272, 144)
        Coordinate displacement(-16, 0);
        game.advance(30);
        game.move(0, displacement);
        std::vector<PlayerInfoDTO> playersInfo = game.getPlayersInfo();
        playersInfo.pop_back();
        const PlayerInfoDTO& juanPlayerInfo = playersInfo.back();
        Coordinate actualPosition( juanPlayerInfo.getCoordinate().getX(),juanPlayerInfo.getCoordinate().getY());
        Coordinate expectedPosition(304,144);
        EXPECT_EQ(expectedPosition, actualPosition);
    }

    TEST(BuyTest, Check) {
        GameParser parser("../maps/test_map.yaml", "../gameConstants/shop.yaml", "../gameConstants/WeaponsConfig.yaml");
        Game game(parser, 10);
        game.addPlayer(0, "juan", Team::COUNTER_TERRORISTS, SEAL_FORCE);
        game.buy(0, ProductType::AK_47_WEAPON);
        std::vector<PlayerInfoDTO> playersInfo = game.getPlayersInfo();
        const PlayerInfoDTO& playerInfo = playersInfo.back();
        std::vector<int> expectedCodes = { 2, 1, 0 };
        std::vector<uint16_t> expectedAmmoAmounts = { 30, 30, 0 };
        bool hasExpectedInfo = true;
        for ( auto& weapon : playerInfo.getWeaponsInfo()) {
            int expectedCode = expectedCodes.back();
            expectedCodes.pop_back();
            uint16_t expectedAmmoAmount = expectedAmmoAmounts.back();
            expectedAmmoAmounts.pop_back();
            hasExpectedInfo =  hasExpectedInfo && ((int)weapon.getWeaponType() == expectedCode);
            hasExpectedInfo = hasExpectedInfo && ( weapon.getAmmoAmount() == expectedAmmoAmount);
        }
        EXPECT_EQ(hasExpectedInfo, true);
    }

    TEST(SelectWeaponTest, Check) {
        GameParser parser("../maps/test_map.yaml", "../gameConstants/shop.yaml", "../gameConstants/WeaponsConfig.yaml");
        Game game(parser, 10);
        game.addPlayer(0, "juan", Team::COUNTER_TERRORISTS, SEAL_FORCE);
        game.addPlayer(1, "carlos", Team::TERRORISTS, PHOENIX);
        game.buy(0, ProductType::AK_47_WEAPON);
        game.advance(30);
        game.setWeapon(0, 1);
        std::vector<PlayerInfoDTO> playersInfo = game.getPlayersInfo();
        const PlayerInfoDTO& playerInfo = playersInfo.at(0);
        int expectedCode = 1;
        uint16_t expectedAmmoAmount = 30;
        int obtainedCode = (int)playerInfo.getActualWeapon().getWeaponType();
        uint16_t obtainedAmmo = playerInfo.getActualWeapon().getAmmoAmount();
        bool hasExpectedInfo =  (obtainedCode == expectedCode) && (obtainedAmmo == expectedAmmoAmount);
        EXPECT_EQ(hasExpectedInfo, true);
    }

    TEST(DropTest, Check) {
        GameParser parser("../maps/test_map.yaml", "../gameConstants/shop.yaml", "../gameConstants/WeaponsConfig.yaml");
        Game game(parser, 10);
        game.addPlayer(0, "juan", Team::COUNTER_TERRORISTS, SEAL_FORCE);
        game.addPlayer(0, "carlos", Team::TERRORISTS, PHOENIX);
        game.buy(0, ProductType::AK_47_WEAPON);
        game.buy(0, ProductType::M3_WEAPON);
        std::vector<PlayerInfoDTO> playersInfo = game.getPlayersInfo();
        const PlayerInfoDTO& playerInfo = playersInfo.at(0);
        WeaponType weaponType = playerInfo.getActualWeapon().getWeaponType();
        bool hasExpectedBuy = weaponType == WeaponType::M3;
        game.advance(30);
        game.takeDrop(0);
        game.setWeapon(0, 2);
        playersInfo = game.getPlayersInfo();
        const PlayerInfoDTO& newPlayerInfo = playersInfo.at(0);
        weaponType = newPlayerInfo.getActualWeapon().getWeaponType();
        bool hasExpectedDrop = weaponType == WeaponType::AK47;
        bool hasExpectedInfo = hasExpectedBuy && hasExpectedDrop;
        EXPECT_EQ(hasExpectedInfo, true);
    }

    TEST(AttackKnifeTest, Check) {
        GameParser parser("../maps/test_map.yaml", "../gameConstants/shop.yaml", "../gameConstants/WeaponsConfig.yaml");
        Game game(parser, 10);
        game.addPlayer(0, "juan", Team::COUNTER_TERRORISTS, SEAL_FORCE);
        game.addPlayer(1, "carlos", Team::TERRORISTS, PHOENIX);
        game.advance(30);
        game.setWeapon(0, 0);
        game.changeAngle(0, Coordinate(-1, 0));
        double actualTime;
        for ( actualTime = 0; actualTime < 2.5; actualTime+= 0.01) {
            game.advance(actualTime);
        }
        game.attack(0);
        for (double i = actualTime; i < actualTime + 2.5; i+= 0.01) {
            double rounded = std::round(i * 100) / 100;
            game.advance(rounded);
        }
        std::vector<PlayerInfoDTO> playersInfo = game.getPlayersInfo();
        PlayerInfoDTO& carlosInfo = playersInfo.back();
        //playersInfo.pop_back();
        //PlayerInfoDTO& juanInfo = playersInfo.back();
        //std::cout << carlosInfo.getName() << " tiene " << (int)carlosInfo.getHealth() << " puntos de vida. pos: (" << carlosInfo.getCoordinate().getX() << ", " << carlosInfo.getCoordinate().getY()<< ")" << std::endl;
        //std::cout << juanInfo.getName() << " tiene " << (int)juanInfo.getHealth() << " puntos de vida. pos: (" << juanInfo.getCoordinate().getX() << ", " << juanInfo.getCoordinate().getY()<< ")" << std::endl;
        bool carlosHasLowerHealth = (int)carlosInfo.getHealth() < 100;
        EXPECT_EQ(carlosHasLowerHealth, true);
    }

    TEST(AttackGlockTest, Check) {
        GameParser parser("../maps/test_map.yaml", "../gameConstants/shop.yaml", "../gameConstants/WeaponsConfig.yaml");
        Game game(parser, 10);
        game.addPlayer(0, "juan", Team::COUNTER_TERRORISTS, SEAL_FORCE);
        game.addPlayer(1, "carlos", Team::TERRORISTS, PHOENIX);
        game.advance(30);
        game.setWeapon(0, 1);
        game.changeAngle(0, Coordinate(-1, 0));
        double actualTime;
        for ( actualTime = 0; actualTime < 2.5; actualTime+= 0.01) {
            game.advance(actualTime);
        }
        game.attack(0);
        for (double i = actualTime; i < actualTime + 2.5; i+= 0.01) {
            double rounded = std::round(i * 100) / 100;
            game.advance(rounded);
        }
        std::vector<PlayerInfoDTO> playersInfo = game.getPlayersInfo();
        PlayerInfoDTO& carlosInfo = playersInfo.back();
        //playersInfo.pop_back();
        //PlayerInfoDTO& juanInfo = playersInfo.back();
        //std::cout << carlosInfo.getName() << " tiene " << (int)carlosInfo.getHealth() << " puntos de vida. pos: (" << carlosInfo.getCoordinate().getX() << ", " << carlosInfo.getCoordinate().getY()<< ")" << std::endl;
        //std::cout << juanInfo.getName() << " tiene " << (int)juanInfo.getHealth() << " puntos de vida. pos: (" << juanInfo.getCoordinate().getX() << ", " << juanInfo.getCoordinate().getY()<< ")" << std::endl;
        bool carlosHasLowerHealth = (int)carlosInfo.getHealth() < 100;
        EXPECT_EQ(carlosHasLowerHealth, true);
    }

    TEST(AttackAkTest, Check) {
        GameParser parser("../maps/test_map.yaml", "../gameConstants/shop.yaml", "../gameConstants/WeaponsConfig.yaml");
        Game game(parser, 10);
        game.addPlayer(0, "juan", Team::COUNTER_TERRORISTS, SEAL_FORCE);
        game.addPlayer(1, "carlos", Team::TERRORISTS, PHOENIX);
        game.buy(0, ProductType::AK_47_WEAPON);
        game.advance(30);
        game.changeAngle(0, Coordinate(-1, 0));
        double actualTime;
        for ( actualTime = 0; actualTime < 2.5; actualTime+= 0.01) {
            game.advance(actualTime);
        }
        game.attack(0);
        for (double i = actualTime; i < actualTime + 2.5; i+= 0.01) {
            double rounded = std::round(i * 100) / 100;
            game.advance(rounded);
        }
        std::vector<PlayerInfoDTO> playersInfo = game.getPlayersInfo();
        PlayerInfoDTO& carlosInfo = playersInfo.back();
        //playersInfo.pop_back();
        //PlayerInfoDTO& juanInfo = playersInfo.back();
        //std::cout << carlosInfo.getName() << " tiene " << (int)carlosInfo.getHealth() << " puntos de vida. pos: (" << carlosInfo.getCoordinate().getX() << ", " << carlosInfo.getCoordinate().getY()<< ")" << std::endl;
        //std::cout << juanInfo.getName() << " tiene " << (int)juanInfo.getHealth() << " puntos de vida. pos: (" << juanInfo.getCoordinate().getX() << ", " << juanInfo.getCoordinate().getY()<< ")" << std::endl;
        bool carlosHasLowerHealth = (int)carlosInfo.getHealth() < 100;
        EXPECT_EQ(carlosHasLowerHealth, true);
    }

    TEST(AttackM3Test, Check) {
        GameParser parser("../maps/test_map.yaml", "../gameConstants/shop.yaml", "../gameConstants/WeaponsConfig.yaml");
        Game game(parser, 10);
        game.addPlayer(0, "juan", Team::COUNTER_TERRORISTS, SEAL_FORCE);
        game.addPlayer(1, "carlos", Team::TERRORISTS, PHOENIX);
        game.buy(0, ProductType::M3_WEAPON);
        double actualTime = 30;
        game.advance(actualTime);
        game.changeAngle(0, Coordinate(-1, 0));
        for ( actualTime = 30; actualTime < 32.5; actualTime+= 0.01) {
            game.advance(actualTime);
        }
        game.attack(0);
        for (double i = actualTime; i < actualTime + 2.5; i+= 0.01) {
            double rounded = std::round(i * 100) / 100;
            game.advance(rounded);
        }
        std::vector<PlayerInfoDTO> playersInfo = game.getPlayersInfo();
        PlayerInfoDTO& carlosInfo = playersInfo.back();
        //playersInfo.pop_back();
        //PlayerInfoDTO& juanInfo = playersInfo.back();
        //std::cout << carlosInfo.getName() << " tiene " << (int)carlosInfo.getHealth() << " puntos de vida. pos: (" << carlosInfo.getCoordinate().getX() << ", " << carlosInfo.getCoordinate().getY()<< ")" << std::endl;
        //std::cout << juanInfo.getName() << " tiene " << (int)juanInfo.getHealth() << " puntos de vida. pos: (" << juanInfo.getCoordinate().getX() << ", " << juanInfo.getCoordinate().getY()<< ")" << std::endl;
        bool carlosHasLowerHealth = (int)carlosInfo.getHealth() < 100;
        EXPECT_EQ(carlosHasLowerHealth, true);
    }

    TEST(AttackAwpTest, Check) {
        GameParser parser("../maps/test_map.yaml", "../gameConstants/shop.yaml", "../gameConstants/WeaponsConfig.yaml");
        Game game(parser, 10);
        game.addPlayer(0, "juan", Team::COUNTER_TERRORISTS, SEAL_FORCE);
        game.addPlayer(1, "carlos", Team::TERRORISTS, PHOENIX);
        game.buy(0, ProductType::AWP_WEAPON);
        double actualTime = 30;
        game.advance(actualTime);
        game.changeAngle(0, Coordinate(-1, 0));
        for ( actualTime = 30; actualTime < 32.5; actualTime+= 0.01) {
            game.advance(actualTime);
        }
        game.attack(0);
        for (double i = actualTime; i < actualTime + 2.5; i+= 0.01) {
            double rounded = std::round(i * 100) / 100;
            game.advance(rounded);
        }
        std::vector<PlayerInfoDTO> playersInfo = game.getPlayersInfo();
        PlayerInfoDTO& carlosInfo = playersInfo.back();
        //playersInfo.pop_back();
        //PlayerInfoDTO& juanInfo = playersInfo.back();
        //std::cout << carlosInfo.getName() << " tiene " << (int)carlosInfo.getHealth() << " puntos de vida. pos: (" << carlosInfo.getCoordinate().getX() << ", " << carlosInfo.getCoordinate().getY()<< ")" << std::endl;
        //std::cout << juanInfo.getName() << " tiene " << (int)juanInfo.getHealth() << " puntos de vida. pos: (" << juanInfo.getCoordinate().getX() << ", " << juanInfo.getCoordinate().getY()<< ")" << std::endl;
        bool carlosHasLowerHealth = (int)carlosInfo.getHealth() < 100;
        EXPECT_EQ(carlosHasLowerHealth, true);
    }

    TEST(PlantBombTest, Check) {
        GameParser parser("../maps/test_map.yaml", "../gameConstants/shop.yaml", "../gameConstants/WeaponsConfig.yaml");
        Game game(parser, 10);
        game.addPlayer(0, "juan", Team::TERRORISTS, PHOENIX);
        game.addPlayer(1, "carlos", Team::COUNTER_TERRORISTS, SEAL_FORCE);
        game.advance(30);
        game.spawnBomb();
        game.setWeapon(0, 3);
        game.attack(0);
        GameInfoDTO gameInfo = game.getInfo();
        GameStatus status = gameInfo.getStatus();
        EXPECT_EQ(status, BOMB_PLANTED);
    }

    TEST(KillSomeOneGivesMoneyTest, Check) {
        GameParser parser("../maps/test_map.yaml", "../gameConstants/shop.yaml", "../gameConstants/WeaponsConfig.yaml");
        Game game(parser, 10);
        game.addPlayer(0, "juan", Team::COUNTER_TERRORISTS, SEAL_FORCE);
        game.addPlayer(1, "carlos", Team::TERRORISTS, PHOENIX);
        game.buy(0, ProductType::AWP_WEAPON);
        double actualTime = 30;
        game.advance(actualTime);
        game.changeAngle(0, Coordinate(-1, 0));
        for ( actualTime = 30; actualTime < 32.5; actualTime+= 0.01) {
            game.advance(actualTime);
        }
        std::vector<PlayerInfoDTO> playersInfo = game.getPlayersInfo();
        PlayerInfoDTO& juanInfo = playersInfo.at(0);
        uint16_t juanInitialMoney = juanInfo.getMoney();
        game.attack(0);
        for (double i = actualTime; i < actualTime + 2.5; i+= 0.01) {
            double rounded = std::round(i * 100) / 100;
            game.advance(rounded);
        }
        game.attack(0);
        for (double i = actualTime; i < actualTime + 2.5; i+= 0.01) {
            double rounded = std::round(i * 100) / 100;
            game.advance(rounded);
        }
        playersInfo = game.getPlayersInfo();
        PlayerInfoDTO& newJuanInfo = playersInfo.at(0);
        uint16_t actualJuanMoney = newJuanInfo.getMoney();
        EXPECT_EQ(actualJuanMoney > juanInitialMoney, true);
    }

    TEST(BombExplosionTest, Check) {
        GameParser parser("../maps/test_map.yaml", "../gameConstants/shop.yaml", "../gameConstants/WeaponsConfig.yaml");
        double bombTimeToExplode = parser.getWeaponInfo(WeaponType::BOMB, "activationTime");
        Game game(parser, 10);
        game.addPlayer(0, "juan", Team::TERRORISTS, PHOENIX);
        game.addPlayer(1, "carlos", Team::COUNTER_TERRORISTS, SEAL_FORCE);
        game.advance(30);
        game.spawnBomb();
        game.setWeapon(0, 3);
        double actualTime = 30;
        game.advance(actualTime);
        game.attack(0);
        for ( actualTime = 30; actualTime <= bombTimeToExplode + 31; actualTime+= 0.01) {
            game.advance(actualTime);
        }
        GameInfoDTO gameInfo = game.getInfo();
        GameStatus status = gameInfo.getStatus();
        EXPECT_EQ(status, TERRORISTS_WIN);
    }

    TEST(BombDeactivationTest, Check) {
        GameParser parser("../maps/test_map.yaml", "../gameConstants/shop.yaml", "../gameConstants/WeaponsConfig.yaml");
        double bombTimeToExplode = parser.getWeaponInfo(WeaponType::BOMB, "activationTime");
        Game game(parser, 10);
        game.addPlayer(0, "juan", Team::TERRORISTS, PHOENIX);
        game.addPlayer(1, "carlos", Team::COUNTER_TERRORISTS, SEAL_FORCE);
        double actualTime = 30;
        game.advance(actualTime);
        game.spawnBomb();
        game.setWeapon(0, 3);
        game.attack(0);
        game.move(0, Coordinate(-32,0));
        game.move(1, Coordinate(-32,0));
        for ( actualTime = 30.01; actualTime <= bombTimeToExplode + 32; actualTime+= 0.01) {
            game.deactivateBomb(1);
            game.advance(actualTime);
        }
        GameInfoDTO gameInfo = game.getInfo();
        GameStatus status = gameInfo.getStatus();
        EXPECT_EQ(status, COUNTERS_WIN);
    }

}



