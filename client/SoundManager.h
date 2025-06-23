#pragma once

#include <unordered_map>

#include <SDL.h>
#include <SDL2pp/Chunk.hh>
#include <SDL2pp/Mixer.hh>
#include <SDL2pp/SDL2pp.hh>

#include "EntityConstants.h"

using namespace SDL2pp;

class SoundManager {
private:
    Mixer mixer;
    std::unordered_map<EntityType, Chunk> closeSoundsMap;
    std::unordered_map<EntityType, Chunk> farSoundsMap;
    std::unordered_map<EntityType, Chunk> drawSoundsMap;

    Chunk ctWins;
    Chunk ctWinswBomb;
    Chunk ttWins;
    Chunk bombPlanted;
    Chunk death;

    void loadCloseSound(const EntityType entity, const std::string& filepath);
    void loadFarSound(const EntityType entity, const std::string& filepath);
    void loadDrawSound(const EntityType entity, const std::string& filepath);

public:
    SoundManager();
    void playCloseSound(const EntityType entityId, int loops = 0);
    void playFarSound(const EntityType entityId, int loops = 0);
    void playDrawSound(const EntityType entityId, int loops = 0);
    void playBombPlanted();
    void playTtWins();
    void playCtWinsBombDefused();
    void playCtWins();
    void playDeathSound();
    bool isPlaying();
    void stopAll();
};
