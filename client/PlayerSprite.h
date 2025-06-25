#pragma once

#include "Constants/ClientConstants.h"
#include "SDL2pp/Renderer.hh"
#include "SDL2pp/Texture.hh"
#include "common/Constants/PlayerStatus.h"
#include "common/DTO/CoordinateInformation.h"
#include "common/DTO/PlayerInformation.h"

#include "SoundManager.h"
#include "TextureManager.h"

constexpr double CLOSE_RANGE_X = RES_WIDTH_BASE;
constexpr double CLOSE_RANGE_Y = RES_HEIGTH_BASE;

class PlayerSprite {

private:
    Renderer& renderer;
    TextureManager& textureManager;
    SoundManager& soundManager;

    PlayerInformation playerInfo;
    PlayerInformation prevPlayerInfo;
    CoordinateInformation offSet;
    CoordinateInformation prevOffSet;
    PlayerStatus prevState;

    bool isClient;
    int frame;

    void renderPlayer();
    void renderHeldWeapon();
    void renderDefusing();
    void renderBullets();
    void renderBullets2();
    void playSound();
    bool isPlayerClose();

public:
    PlayerSprite(Renderer& renderer, TextureManager& textureManager, SoundManager& soundManager,
                 PlayerInformation info, bool isClient = false);

    void update(const PlayerInformation info, const CoordinateInformation offset);
    void render();
};
