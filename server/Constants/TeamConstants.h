#pragma once

#include <cstdint>

enum Team : uint8_t {
    TERRORISTS = 0x00,
    COUNTER_TERRORISTS = 0x01
};

enum TerroristSkin : uint8_t {
    PHOENIX = 0x00,
    L337_KREW = 0x01,
    ARCTIC_AVENGER = 0x02,
    GUERRILLA = 0x03
};

enum CounterTerroristSkin : uint8_t {
    SEAL_FORCE = 0x00,
    GERMAN_GSG9 = 0x01,
    UK_SAS = 0x02,
    FRENCH_GIGN = 0x03
};



