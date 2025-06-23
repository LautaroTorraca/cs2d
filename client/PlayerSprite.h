#pragma once

#include "Constants/ClientConstants.h"
#include "SDL2pp/Renderer.hh"
#include "SDL2pp/Texture.hh"

#include "CoordinateInformation.h"
#include "PlayerInformation.h"
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
    bool isClient;
    int frame;
    Texture& skin;

    void renderPlayer();
    void renderHeldWeapon();
    void renderBullets();
    void playSound();
    bool isPlayerClose();

public:
    PlayerSprite(Renderer& renderer, TextureManager& textureManager, SoundManager& soundManager,
                 PlayerInformation info, bool isClient = false);

    void update(const PlayerInformation info, const CoordinateInformation offset);
    void render();
};
