#pragma once

enum OrderType {
    // Valores comunes
    DO_NOTHING = -1,

    // Valores de Lobby (1-100)
    LOBBY_LIST = 1,
    LOBBY_CREATE = 2,
    LOBBY_JOIN = 3,
    LOBBY_DISCONNECT = 100,

    // Valores de Game Lobby (101-200)
    GAME_LOBBY_SELECT_TEAM = 101,
    GAME_LOBBY_SELECT_SKIN = 102,
    GAME_LOBBY_READY = 103,
    GAME_LOBBY_EXIT = 200,

    // Valores de In Game (201-300)
    IN_GAME_MOVE = 201,
    IN_GAME_SHOOT = 202,
    IN_GAME_PICK_UP_ITEM = 203,
    IN_GAME_DROP_ITEM = 204,
    IN_GAME_BUY_AMMO = 205,
    IN_GAME_BUY_WEAPON = 206,
    IN_GAME_SWITCH_WEAPON = 207,
    IN_GAME_PLANT_BOMB = 208,
    IN_GAME_DEFUSE_BOMB = 209,
    IN_GAME_EXIT = 300
};
