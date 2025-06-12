#pragma once

#include <cstdint>

namespace ProtocolConstants {

enum Opcode : uint8_t {
  // Solicitudes del Cliente (0x00 -> 0x0F)
  CREATE_GAME = 1,
  JOIN_GAME = 2,
  GAME_LIST_REQUEST = 3,
  DISCONNECT = 15,

  // Preparación del Juego (0x10 -> 0x1F)
  READY = 100,
  EXIT_LOBBY = 200,

  // Durante el Juego (0x20 -> 0x2F)
    PLAYER_MOVEMENT = 201,
    ATTACK = 202,
    PICK_UP_ITEM = 203,
    DROP_ITEM = 204,
    BUY = 205,
    CHANGE_ANGLE = 206,
    SWITCH_WEAPON = 207,
    PLANT_BOMB = 208,
    DEFUSE_BOMB = 209,
    EXIT_GAME = 255
};

}
