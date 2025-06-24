#include <cmath>
// #include <iostream>

#include "Constants/ClientConstants.h"
#include "server/PlayerStatus.h"

#include "EntityConstants.h"
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
        // skin(textureManager.getSkin(info.skin)),
        prevState(PlayerStatus::LIVING) {}

void PlayerSprite::update(const PlayerInformation newPlayerInfo,
                          const CoordinateInformation offset) {
    prevPlayerInfo = playerInfo;
    prevPlayerInfo.skin = playerInfo.skin;

    prevState = playerInfo.status;

    playerInfo = newPlayerInfo;
    // playerInfo.skin = newPlayerInfo.skin;

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
        renderDefusing();
        renderBullets2();
        renderHeldWeapon();
    } else if (isClient) {
        textureManager.getSkin(playerInfo.skin).SetColorAndAlphaMod({40, 210, 210, 90});
        renderPlayer();
        textureManager.getSkin(playerInfo.skin).SetColorAndAlphaMod({255, 255, 255, 255});
    }
    playSound();
}

bool PlayerSprite::isPlayerClose() {

    return ((abs(offSet.x - playerInfo.position.x)) <= CLOSE_RANGE_X &&
            (abs(offSet.y - playerInfo.position.y)) <= CLOSE_RANGE_Y);
}
void PlayerSprite::playSound() {

    if (prevState != PlayerStatus::DEAD && playerInfo.status == PlayerStatus::DEAD) {
        soundManager.playDeathSound();
    }

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

    renderer.Copy(textureManager.getSkin(playerInfo.skin),
                  Rect(posSrcX, posSrcY, TILE_SRC_SIZE, TILE_SRC_SIZE),
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

void PlayerSprite::renderDefusing() {
    if (playerInfo.status != PlayerStatus::DEFUSING || !isClient) {
        return;
    }
    Texture font = textureManager.getFont(15, "defusing", {0, 255, 0, 180});
    renderer.Copy(font, SDL2pp::NullOpt, {200, 200});
}

void PlayerSprite::renderBullets() {
    if ((EntityType)playerInfo.actualWeapon.weaponType == EntityType::KNIFE)
        return;
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

void PlayerSprite::renderBullets2() {
    if ((EntityType)playerInfo.actualWeapon.weaponType == EntityType::KNIFE)
        return;

    renderer.SetDrawColor(235, 255, 0, 255);

    for (const auto& bullet: playerInfo.actualWeapon.projectilesInfo) {
        int x = static_cast<int>(bullet.projectilePosition.x - offSet.x);
        int y = static_cast<int>(bullet.projectilePosition.y - offSet.y);

        SDL_Rect bulletRect = {x - 1, y - 1, 2, 2};
        renderer.FillRect(bulletRect);
    }

    renderer.SetDrawColor(0, 0, 0, 255);
}
