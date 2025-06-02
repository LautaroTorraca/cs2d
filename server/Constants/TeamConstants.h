#pragma once

#include "Team.h"
#include <cstdint>

enum Skin : uint8_t {
  // TT
  PHOENIX = 0x00,
  L337_KREW = 0x01,
  ARCTIC_AVENGER = 0x02,
  GUERRILLA = 0x03,

  // CT
  SEAL_FORCE = 0x10,
  GERMAN_GSG9 = 0x11,
  UK_SAS = 0x12,
  FRENCH_GIGN = 0x13
};

namespace TeamConstants {
constexpr uint8_t TERRORISTS = Team::TERRORISTS;
constexpr uint8_t COUNTER_TERRORISTS = Team::COUNTER_TERRORISTS;
} // namespace TeamConstants

namespace SkinConstants {
constexpr uint8_t PHOENIX = Skin::PHOENIX;
constexpr uint8_t L337_KREW = Skin::L337_KREW;
constexpr uint8_t ARCTIC_AVENGER = Skin::ARCTIC_AVENGER;
constexpr uint8_t GUERRILLA = Skin::GUERRILLA;

constexpr uint8_t SEAL_FORCE = Skin::SEAL_FORCE;
constexpr uint8_t GERMAN_GSG9 = Skin::GERMAN_GSG9;
constexpr uint8_t UK_SAS = Skin::UK_SAS;
constexpr uint8_t FRENCH_GIGN = Skin::FRENCH_GIGN;
} // namespace SkinConstants
