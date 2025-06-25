#include "ExplotionSprite.h"

#include "DTO/CoordinateInformation.h"
#include "SDL2pp/Renderer.hh"
#include "SDL2pp/Texture.hh"

#include "EntityConstants.h"
#include "SoundManager.h"

ExplotionSprite::ExplotionSprite(Renderer& renderer, Texture& texture, SoundManager& soundManager):
        sprite(texture), renderer(renderer), soundManager(soundManager) {}

int ExplotionSprite::getFrame() {
    int returnFrame = lastFrame;
    lastFrame++;
    return returnFrame;
}

void ExplotionSprite::start() {
    ongoing = true;
    lastFrame = 0;
    soundManager.playCloseSound(EntityType::BOMB);
}
bool ExplotionSprite::ended() {
    ongoing = lastFrame < MAX_FRAME;
    return !ongoing;
}
void ExplotionSprite::draw(CoordinateInformation pos) {

    int expSz = 256;
    if (ended())
        return;

    int frame = getFrame();

    int textureX = 64 * (frame % 5);
    int div = (frame / 5);
    int textureY = 64 * div;

    renderer.Copy(sprite, Rect(textureX, textureY, 64, 64),
                  Rect(pos.x - (expSz / 2.0), pos.y - (expSz / 2.0), expSz, expSz));
}
