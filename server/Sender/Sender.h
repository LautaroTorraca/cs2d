
#ifndef SENDER_H
#define SENDER_H


#include <functional>
#include <map>
#include <string>
#include <vector>

#include <bits/stdint-uintn.h>

#include "common/socket.h"
#include "server/DropDTO.h"
#include "server/PlayerInfoDTO.h"

#include "server/ProductType.h"

class Sender {
  Socket& socket;
public:
  explicit Sender(Socket& socket) : socket(socket) {}

  void send(const std::string &data);

  void send(const uint8_t &data);

  void send(const uint16_t &data);

  void send(const size_t &data);

  void bytesChecker(const int &sendBytes);

  void send(const std::vector<std::vector<uint8_t>> & map);

  void send(const PlayerInfoDTO & player_info);

  void send(const WeaponInfoDTO &weaponInfo);

  void send(const ProjectileDTO &projectileInfo);

  void send(const CoordinateDTO &coordinate);

  void send(const double &data);

  void send(const DropDTO& drop);
    void send(const std::map<ProductType, double>& shopInfo);
};

#endif // SENDER_H
