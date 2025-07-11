#pragma once

enum OrderType {
    // Valores comunes
    DO_NOTHING = -1,

    // Valores de Lobby (1-100)
    LOBBY_CREATE = 1,
    LOBBY_JOIN = 2,
    LOBBY_LIST = 3,
    LOBBY_DISCONNECT = 15,

    // Valores de Game Lobby (101-200)
    GAME_LOBBY_READY = 100,
    GAME_LOBBY_EXIT = 200,

    // Valores de In Game (201-300)
    IN_GAME_MOVE = 201,
    IN_GAME_SHOOT = 202,
    IN_GAME_PICK_UP_ITEM = 203,
    IN_GAME_DROP_ITEM = 204,
    IN_GAME_BUY = 205,
    IN_GAME_CHANGE_ANGLE = 206,
    IN_GAME_SWITCH_WEAPON = 207,
    IN_GAME_PLANT_BOMB = 208,
    IN_GAME_DEFUSE_BOMB = 209,
    IN_GAME_EXIT = 255
};
