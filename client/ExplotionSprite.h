#pragma once
#include "SDL2pp/Renderer.hh"
#include "SDL2pp/Texture.hh"

#include "CoordinateInformation.h"
#include "SoundManager.h"
#define MAX_FRAME 22

using namespace SDL2pp;

class ExplotionSprite {
private:
    Texture& sprite;
    Renderer& renderer;
    SoundManager& soundManager;
    int lastFrame = 0;

    bool ongoing;
    int getFrame();

public:
    ExplotionSprite(Renderer& renderer, Texture& texture, SoundManager& soundManager);
    bool ended();
    void start();
    void draw(CoordinateInformation pos);
};
