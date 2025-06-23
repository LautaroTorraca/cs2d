#pragma once
#include "SDL2pp/Renderer.hh"
#include "SDL2pp/Texture.hh"

// #include "CoordinateInformation.h"
// #define MAX_FRAME 22

using namespace SDL2pp;

class PlayerSprite {
private:
    // Texture& sprite;
    // Renderer& renderer;
    // int lastFrame = 0;
    //
    // bool ongoing;
    // int getFrame();

public:
    PlayerSprite(Renderer& renderer, Texture& texture);
    // bool ended();
    // void start();
    // void draw(CoordinateInformation pos);
};
