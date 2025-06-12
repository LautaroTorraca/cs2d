#pragma once
constexpr std::size_t SINGLE_VALUE = 1;

constexpr uint8_t OPCODE_CREATE_GAME = 0x01;
constexpr uint8_t OPCODE_JOIN_GAME = 0x02;
constexpr uint8_t OPCODE_LIST_GAMES = 0x03;
constexpr uint8_t OPCODE_DISCONNECT = 0x0F;



constexpr uint8_t OPCODE_READY = 100;
constexpr uint8_t OPCODE_EXIT_LOBBY = 200;


constexpr uint8_t OPCODE_PLAYER_MOVEMENT = 201;
constexpr uint8_t OPCODE_SHOOT = 202;
constexpr uint8_t OPCODE_BUY = 205;
constexpr uint8_t OPCODE_CHANGE_ANGLE = 206;
constexpr uint8_t OPCODE_PICK_UP_ITEM = 203;
constexpr uint8_t OPCODE_DROP_ITEM = 204;
constexpr uint8_t OPCODE_SWITCH_WEAPON = 207;
constexpr uint8_t OPCODE_PLANT_BOMB = 208;
constexpr uint8_t OPCODE_DEFUSE_BOMB = 209;
constexpr uint8_t OPCODE_EXIT_GAME = 255;



constexpr uint16_t moveUp = 0;
constexpr uint16_t moveRight = 1;
constexpr uint16_t moveDown = 2;
constexpr uint16_t moveLeft = 3;

constexpr uint8_t NEW = 0x6E;
constexpr uint8_t STOP = 0x73;
