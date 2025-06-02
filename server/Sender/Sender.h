
#ifndef SENDER_H
#define SENDER_H

#include <string>
#include <bits/stdint-uintn.h>

#include "ClientHandler.h"
#include "common/socket.h"

class Sender {
  Socket& socket;
public:
  explicit Sender(Socket& socket) : socket(socket) {}

  void send(std::string data);

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

  void send(const DropDTO & drop);
};

#endif // SENDER_H
