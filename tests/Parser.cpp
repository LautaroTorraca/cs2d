#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "server/GameParser.h"

using ::testing::AllOf;
using ::testing::HasSubstr;
using ::testing::ThrowsMessage;


namespace {
TEST(MapParserTest, Check) {
    GameParser parser("../maps/test_map.yaml", "../gameConstants/shop.yaml",
                      "../gameConstants/WeaponsConfig.yaml");

    std::vector<Coordinate> expectedPsthCoordinates;
    expectedPsthCoordinates.emplace_back(4, 0);
    expectedPsthCoordinates.emplace_back(4, 1);
    expectedPsthCoordinates.emplace_back(4, 2);
    expectedPsthCoordinates.emplace_back(4, 3);
    expectedPsthCoordinates.emplace_back(4, 4);
    expectedPsthCoordinates.emplace_back(5, 0);
    expectedPsthCoordinates.emplace_back(5, 1);
    expectedPsthCoordinates.emplace_back(5, 2);
    expectedPsthCoordinates.emplace_back(5, 3);
    expectedPsthCoordinates.emplace_back(5, 4);
    expectedPsthCoordinates.emplace_back(6, 0);
    expectedPsthCoordinates.emplace_back(6, 1);
    expectedPsthCoordinates.emplace_back(6, 2);
    expectedPsthCoordinates.emplace_back(6, 3);
    expectedPsthCoordinates.emplace_back(6, 4);
    expectedPsthCoordinates.emplace_back(7, 3);
    expectedPsthCoordinates.emplace_back(7, 4);
    expectedPsthCoordinates.emplace_back(8, 3);
    expectedPsthCoordinates.emplace_back(8, 4);
    expectedPsthCoordinates.emplace_back(9, 3);
    expectedPsthCoordinates.emplace_back(9, 4);

    std::vector<Coordinate> expectedCountersSpawnPoints;
    expectedCountersSpawnPoints.emplace_back(7, 3);
    expectedCountersSpawnPoints.emplace_back(8, 3);
    expectedCountersSpawnPoints.emplace_back(9, 3);
    expectedCountersSpawnPoints.emplace_back(7, 4);
    expectedCountersSpawnPoints.emplace_back(8, 4);
    expectedCountersSpawnPoints.emplace_back(9, 4);

    std::vector<Coordinate> expectedTerroristsSpawnPoints;
    expectedTerroristsSpawnPoints.emplace_back(4, 0);
    expectedTerroristsSpawnPoints.emplace_back(5, 0);
    expectedTerroristsSpawnPoints.emplace_back(6, 0);
    expectedTerroristsSpawnPoints.emplace_back(4, 1);
    expectedTerroristsSpawnPoints.emplace_back(5, 1);
    expectedTerroristsSpawnPoints.emplace_back(6, 1);

    std::map<Coordinate, Path> path = parser.getMapPath();
    bool haveAllExpectedCoordinates = true;
    for (Coordinate& coordinate: expectedPsthCoordinates) {
        if (!path.contains(coordinate)) {
            haveAllExpectedCoordinates = false;
            break;
        }
    }
    EXPECT_EQ(haveAllExpectedCoordinates, true);
}

TEST(MapParserSpawns, Check) {
    GameParser parser("../maps/test_map.yaml", "../gameConstants/shop.yaml",
                      "../gameConstants/WeaponsConfig.yaml");

    std::vector<Coordinate> expectedCountersSpawnPoints;
    expectedCountersSpawnPoints.emplace_back(7, 3);
    expectedCountersSpawnPoints.emplace_back(8, 3);
    expectedCountersSpawnPoints.emplace_back(9, 3);
    expectedCountersSpawnPoints.emplace_back(7, 4);
    expectedCountersSpawnPoints.emplace_back(8, 4);
    expectedCountersSpawnPoints.emplace_back(9, 4);

    std::vector<Coordinate> expectedTerroristsSpawnPoints;
    expectedTerroristsSpawnPoints.emplace_back(4, 0);
    expectedTerroristsSpawnPoints.emplace_back(5, 0);
    expectedTerroristsSpawnPoints.emplace_back(6, 0);
    expectedTerroristsSpawnPoints.emplace_back(4, 1);
    expectedTerroristsSpawnPoints.emplace_back(5, 1);
    expectedTerroristsSpawnPoints.emplace_back(6, 1);

    std::vector<Coordinate> countersSpawnPoints = parser.getCountersSpawnPoints();
    bool haveAllExpectedCoordinates = true;
    for (Coordinate& coordinate: expectedCountersSpawnPoints) {
        if (std::find(countersSpawnPoints.begin(), countersSpawnPoints.end(), coordinate) ==
            countersSpawnPoints.end()) {
            haveAllExpectedCoordinates = false;
            break;
        }
    }

    std::vector<Coordinate> terroristsSpawnPoints = parser.getTerroristsSpawnPoints();
    for (Coordinate& coordinate: expectedTerroristsSpawnPoints) {
        if (std::find(terroristsSpawnPoints.begin(), terroristsSpawnPoints.end(), coordinate) ==
            terroristsSpawnPoints.end()) {
            haveAllExpectedCoordinates = false;
            break;
        }
    }

    EXPECT_EQ(haveAllExpectedCoordinates, true);
}

TEST(WeaponsParserInfo, Check) {
    GameParser parser("../maps/test_map.yaml", "../gameConstants/shop.yaml",
                      "../gameConstants/WeaponsConfig.yaml");

    double knifeMinDamage = parser.getWeaponInfo(WeaponType::KNIFE, "minDamage");
    double knifeMaxDamage = parser.getWeaponInfo(WeaponType::KNIFE, "maxDamage");
    double knifeRange = parser.getWeaponInfo(WeaponType::KNIFE, "range");
    double knifeSpeed = parser.getWeaponInfo(WeaponType::KNIFE, "speed");
    double expectedMinDamage = 10;
    double expectedMaxDamage = 20;
    double expectedRange = 32;
    double expectedSpeed = 10;
    bool haveAllExpectedValues = knifeMinDamage == expectedMinDamage &&
                                 knifeMaxDamage == expectedMaxDamage &&
                                 knifeRange == expectedRange && knifeSpeed == expectedSpeed;
    EXPECT_EQ(haveAllExpectedValues, true);
}
}  // namespace
