#include <cmath>

#include "Constants/ClientConstants.h"

#include "PlayerInformation.h"
#include "PlayerSprite.h"
#include "SoundManager.h"

PlayerSprite::PlayerSprite(SDL2pp::Renderer& renderer, TextureManager& textureManager,
                           SoundManager& soundManager, PlayerInformation info, bool isClient):
        renderer(renderer),
        textureManager(textureManager),
        soundManager(soundManager),
        playerInfo(info),
        prevPlayerInfo(info),
        frame(0),
        isClient(isClient),
        skin(textureManager.getSkin(info.skin)) {}

void PlayerSprite::update(const PlayerInformation newPlayerInfo,
                          const CoordinateInformation offset) {
    prevPlayerInfo = playerInfo;
    playerInfo = newPlayerInfo;
    prevOffSet = offSet;
    offSet = offset;

    if ((EntityType)newPlayerInfo.actualWeapon.weaponType == EntityType::KNIFE ||
        (EntityType)newPlayerInfo.actualWeapon.weaponType == EntityType::BOMB) {
        frame = 1;
    } else {
        frame = 3;
    }
}

void PlayerSprite::render() {

    if (playerInfo.status != PlayerStatus::DEAD) {
        renderPlayer();
        renderBullets();
        renderHeldWeapon();
        playSound();
    } else if (isClient) {
        skin.SetColorAndAlphaMod({40, 210, 210, 90});
        renderPlayer();
        skin.SetColorAndAlphaMod({255, 255, 255, 255});
    }
}

bool PlayerSprite::isPlayerClose() {

    return ((abs(offSet.x - playerInfo.position.x)) <= CLOSE_RANGE_X &&
            (abs(offSet.y - playerInfo.position.y)) <= CLOSE_RANGE_Y);
}
void PlayerSprite::playSound() {


    if (prevPlayerInfo.actualWeapon.weaponType == playerInfo.actualWeapon.weaponType) {

        if (prevPlayerInfo.actualWeapon.ammoAmount == playerInfo.actualWeapon.ammoAmount)
            return;

        if (prevPlayerInfo.actualWeapon.ammoAmount > playerInfo.actualWeapon.ammoAmount) {

            if (isPlayerClose())
                soundManager.playCloseSound(
                        static_cast<EntityType>(playerInfo.actualWeapon.weaponType));
            else
                soundManager.playFarSound(
                        static_cast<EntityType>(playerInfo.actualWeapon.weaponType));
        }
    } else {
        soundManager.playDrawSound(static_cast<EntityType>(playerInfo.actualWeapon.weaponType));
    }
}

void PlayerSprite::renderPlayer() {
    int posSrcX = TILE_SRC_SIZE * (frame % 2);
    int posSrcY = TILE_SRC_SIZE * (frame / 2);

    int offsetX = PLAYER_WIDTH / 2.0;
    int offsetY = PLAYER_HEIGTH / 2.0;

    int x = playerInfo.position.x - offSet.x - offsetX;
    int y = playerInfo.position.y - offSet.y - offsetY;

    renderer.Copy(skin, Rect(posSrcX, posSrcY, TILE_SRC_SIZE, TILE_SRC_SIZE),
                  Rect(x, y, PLAYER_WIDTH, PLAYER_HEIGTH), playerInfo.angle);
}

void PlayerSprite::renderHeldWeapon() {
    Texture& weaponTex =
            textureManager.getWeaponHeld((EntityType)playerInfo.actualWeapon.weaponType);

    int offsetX = PLAYER_WIDTH / 2.0;
    int offsetY = PLAYER_HEIGTH / 2.0;
    int x = playerInfo.position.x - offSet.x - offsetX + 2;
    int y = playerInfo.position.y - offSet.y - offsetY - 5;

    Point pivot(16 - 2, 16 + 5);
    renderer.Copy(weaponTex, NullOpt, Rect(x, y, PLAYER_WIDTH, PLAYER_HEIGTH), playerInfo.angle,
                  pivot);
}

void PlayerSprite::renderBullets() {
    renderer.SetDrawColor(255, 255, 0, 0);
    for (const auto& bullet: playerInfo.actualWeapon.projectilesInfo) {
        double dx = bullet.projectilePosition.x - playerInfo.position.x;
        double dy = bullet.projectilePosition.y - playerInfo.position.y;
        renderer.DrawLine(playerInfo.position.x - offSet.x, playerInfo.position.y - offSet.y,
                          bullet.projectilePosition.x - offSet.x,
                          bullet.projectilePosition.y - offSet.y);
    }
    renderer.SetDrawColor(0, 0, 0, 255);
}
