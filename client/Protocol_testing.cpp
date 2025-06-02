#include "Protocol_testing.h"
#include "Constants/ClientConstants.h"
#include "MoveConstants.h"
#include "common/Constants/SnapshotConstants.h"
// #include "server/Constants/ProtocolContants.h"
#include <string>

ProtocolTesting::ProtocolTesting(const std::string &port,
                                 const std::string &hostName)
    : portDummy(port), hostDummy(hostName) {
  fillDummies(gameSnapshot);
}

void ProtocolTesting::move(const Direction &direction) {

  Coords movement;
  movement.x = 0;
  movement.y = 0;
  int movSpeed = 8;
  switch (direction) {
  case Up:
    movement.y -= movSpeed;
    break;
  case Down:
    movement.y += movSpeed;
    break;
  case Left:
    movement.x -= movSpeed;
    break;
  case Right:
    movement.x += movSpeed;
    break;
  }

  for (PlayerData &player : gameSnapshot.game.players) {
    if (player.id == gamePreSnapshot.clientId) {
      player.coords.x += movement.x;
      player.coords.y += movement.y;
      break;
    }
  }
}
void ProtocolTesting::angle(double angleInDegree) {

  for (PlayerData &player : gameSnapshot.game.players) {
    if (player.id == gamePreSnapshot.clientId) {
      player.angle = angleInDegree;
      break;
    }
  }
}

Snapshot ProtocolTesting::receiveSnapshot() { return gameSnapshot; }

PreSnapshot ProtocolTesting::receivePreSnapshot() {
  std::vector<std::vector<int>> tileMap(MAP_HEIGHT,
                                        std::vector<int>(MAP_WIDTH, 30));
  tileMap[4][0] = 60;
  tileMap[4][1] = 61;
  tileMap[4][2] = 62;

  gamePreSnapshot.clientId = 1234;
  gamePreSnapshot.tileMap = tileMap;

  return gamePreSnapshot;
}
