#pragma once
constexpr std::size_t SINGLE_VALUE = 1;

constexpr uint8_t OPCODE_CREATE_GAME = 0x01;
constexpr uint8_t OPCODE_JOIN_GAME = 0x02;
constexpr uint8_t OPCODE_LIST_GAMES = 0x03;
constexpr uint8_t OPCODE_DISCONNECT = 0x0F;


constexpr uint8_t OPCODE_SELECT_TEAM = 0x10;
constexpr uint8_t OPCODE_SELECT_SKIN = 0x11;
constexpr uint8_t OPCODE_READY = 0x12;
constexpr uint8_t OPCODE_EXIT_LOBBY = 0x1F;


constexpr uint8_t OPCODE_PLAYER_MOVEMENT = 0x20;
constexpr uint8_t OPCODE_SHOOT = 0x22;
constexpr uint8_t OPCODE_BUY_AMMO = 0x23;
constexpr uint8_t OPCODE_BUY_WEAPON = 0x24;
constexpr uint8_t OPCODE_PICK_UP_ITEM = 0x25;
constexpr uint8_t OPCODE_DROP_ITEM = 0x26;
constexpr uint8_t OPCODE_SWITCH_WEAPON = 0x27;
constexpr uint8_t OPCODE_PLANT_BOMB = 0x28;
constexpr uint8_t OPCODE_DEFUSE_BOMB = 0x29;
constexpr uint8_t OPCODE_EXIT_GAME = 0x2F;



constexpr uint8_t moveUp = 0x00;
constexpr uint8_t moveRight = 0x01;
constexpr uint8_t moveDown = 0x02;
constexpr uint8_t moveLeft = 0x03;


