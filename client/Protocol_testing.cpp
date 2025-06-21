#include "Protocol_testing.h"

#include <cmath>
// #include <iostream>

#include "Constants/ClientConstants.h"
#include "common/Constants/SnapshotConstants.h"

// #include "CoordinateInformation.h"
// #include "PlayerInformation.h"
// #include "ProjectileInformation.h"


ProtocolTesting::ProtocolTesting(const std::string& hostName, const std::string& port):
        Protocol(hostName, port),
        snapshot(gameStatus, currentRound, countersWins, terroristsWins, playersInfo, drops,
                 bombPosition, 0, 0, 0) {
    fillDummies(snapshot);
}
//
// void ProtocolTesting::move(const Direction& direction) {
//     CoordinateInformation movement;
//     movement.x = 0;
//     movement.y = 0;
//     int movSpeed = 8;
//     switch (direction) {
//         case Up:
//             movement.y -= movSpeed;
//             break;
//         case Down:
//             movement.y += movSpeed;
//             break;
//         case Left:
//             movement.x -= movSpeed;
//             break;
//         case Right:
//             movement.x += movSpeed;
//             break;
//     }
//     for (PlayerInformation& player: snapshot.playersInfo) {
//         if (player.id == clientID) {
//             player.position.x += movement.x;
//             player.position.y += movement.y;
//             player.actualHealthPoints--;
//             break;
//         }
//     }
// }
//
//
// // void ProtocolTesting::emptyBullets() {
// //
// //     for (PlayerInformation& player: snapshot.playersInfo) {
// //         if (player.id == clientID) {
// //             player.actualWeapon.projectilesInfo.clear();
// //             break;
// //         }
// //     }
// // }
//
// void ProtocolTesting::attack() {
//
//     for (PlayerInformation& player: snapshot.playersInfo) {
//         if (player.id == clientID) {
//
//
//             ProjectileInformation bullet({50, 50});
//             player.actualWeapon.projectilesInfo.push_back(bullet);
//             player.actualWeapon.ammoAmount--;
//             break;
//         }
//     }
// }
//
// void ProtocolTesting::changeAngle(const PositionDTO& positionInfo) {
//     for (PlayerInformation& player: snapshot.playersInfo) {
//         if (player.id == clientID) {
//
//             double dx = positionInfo.x - (static_cast<double>(RES_WIDTH) / 2);
//             double dy = positionInfo.y - (static_cast<double>(RES_HEIGTH) / 2);
//             double angleInRads = atan2(dy, dx);
//             double angleInDegree = 180.0 * angleInRads / M_PI;
//             angleInDegree += 90;
//             player.angle = angleInDegree;
//             break;
//         }
//     }
// }
//
// Snapshot ProtocolTesting::receiveSnapshot() const { return snapshot; }
//
// PreSnapshot ProtocolTesting::receivePreSnapshot() const {
//
//     std::vector<std::vector<uint8_t>> tileMap(MAP_HEIGHT, std::vector<uint8_t>(MAP_WIDTH, 30));
//     tileMap[4][0] = 60;
//     tileMap[4][1] = 61;
//     tileMap[4][2] = 62;
//
//
//     return PreSnapshot(clientID, tileMap);
// }
