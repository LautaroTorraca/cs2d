#include "Explotion.h"

#include "SDL2pp/Renderer.hh"
#include "SDL2pp/Texture.hh"

#include "CoordinateInformation.h"

ExplotionSprite::ExplotionSprite(Renderer& renderer, Texture& texture):
        sprite(texture), lastFrame(0), renderer(renderer) {}

int ExplotionSprite::getFrame() {
    int returnFrame = lastFrame;
    lastFrame++;
    return returnFrame;
}

// Texture& ExplotionSprite::getSprite() { return sprite; }
bool ExplotionSprite::ongoing() { return lastFrame < MAX_FRAME; }
bool ExplotionSprite::ended() { return lastFrame >= MAX_FRAME; }
void ExplotionSprite::draw(CoordinateInformation pos) {

    int expSz = 256;
    if (ended()) {
        lastFrame = 0;
        return;
    }

    int frame = getFrame();

    int textureX = 64 * (frame % 5);
    int div = (frame / 5);
    int textureY = 64 * div;

    renderer.Copy(sprite, Rect(textureX, textureY, 64, 64),
                  Rect(pos.x - (expSz / 2.0), pos.y - (expSz / 2.0), expSz, expSz));
}
