#pragma once

#include <cstdint>

namespace ProtocolConstants {

enum Opcode : uint8_t {
  // Solicitudes del Cliente (0x00 -> 0x0F)
  CREATE_GAME = 0x01,
  JOIN_GAME = 0x02,
  GAME_LIST_REQUEST = 0x03,
  DISCONNECT = 0x0F,

  // Preparación del Juego (0x10 -> 0x1F)
  READY = 0x12,
  EXIT_LOBBY = 0x1F,

  // Durante el Juego (0x20 -> 0x2F)
  PLAYER_MOVEMENT = 0x20,
  ATTACK = 0x22,
  BUY = 0x23,
  CHANGE_ANGLE = 0x24,
  PICK_UP_ITEM = 0x25,
  DROP_ITEM = 0x26,
  SWITCH_WEAPON = 0x27,
  PLANT_BOMB = 0x28,
  DEFUSE_BOMB = 0x29,
  EXIT_GAME = 0x2F
};

}
