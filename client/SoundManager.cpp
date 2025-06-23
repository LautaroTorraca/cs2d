#include "SoundManager.h"

#include "EntityConstants.h"


SoundManager::SoundManager():
        mixer(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 4096) {

    mixer.SetVolume(-1, 10);
    mixer.AllocateChannels(32);
    loadCloseSound(EntityType::AK47, "../client/assets/sounds/ak47.wav");
    loadFarSound(EntityType::AK47, "../client/assets/sounds/ak47-distant.wav");
    loadDrawSound(EntityType::AK47, "../client/assets/sounds/ak47_draw.ogg");

    loadCloseSound(EntityType::AWP, "../client/assets/sounds/awp.wav");
    loadFarSound(EntityType::AWP, "../client/assets/sounds/awp-distant.wav");
    loadDrawSound(EntityType::AWP, "../client/assets/sounds/awp_draw.ogg");

    loadCloseSound(EntityType::M3, "../client/assets/sounds/m3.wav");
    loadFarSound(EntityType::M3, "../client/assets/sounds/m3-distant.wav");
    loadDrawSound(EntityType::M3, "../client/assets/sounds/m3_draw.ogg");

    loadCloseSound(EntityType::GLOCK, "../client/assets/sounds/glock.wav");
    loadFarSound(EntityType::GLOCK, "../client/assets/sounds/glock-distant.wav");
    loadDrawSound(EntityType::GLOCK, "../client/assets/sounds/glock_draw.ogg");
}


void SoundManager::loadDrawSound(const EntityType entity, const std::string& filepath) {
    drawSoundsMap.emplace(entity, SDL2pp::Chunk(filepath));
}

void SoundManager::loadFarSound(const EntityType entity, const std::string& filepath) {
    farSoundsMap.emplace(entity, SDL2pp::Chunk(filepath));
}

void SoundManager::loadCloseSound(const EntityType entity, const std::string& filepath) {
    closeSoundsMap.emplace(entity, SDL2pp::Chunk(filepath));
}

void SoundManager::playDrawSound(const EntityType entityId, int loops) {
    if (drawSoundsMap.contains(entityId)) {
        mixer.PlayChannel(-1, drawSoundsMap.at(entityId), loops);
    }
}

void SoundManager::playFarSound(const EntityType entityId, int loops) {
    if (farSoundsMap.contains(entityId)) {
        mixer.PlayChannel(-1, farSoundsMap.at(entityId), loops);
    }
}

void SoundManager::playCloseSound(const EntityType entityId, int loops) {
    if (closeSoundsMap.contains(entityId)) {
        mixer.PlayChannel(-1, closeSoundsMap.at(entityId), loops);
    }
}

void SoundManager::stopAll() { mixer.HaltChannel(-1); }
