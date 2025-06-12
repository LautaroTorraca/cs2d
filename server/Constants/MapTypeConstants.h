#pragma once
#include <cstdint>

enum class MapType : uint8_t {
    DUST = 0x00,
    AZTEC_VILLAGE = 0x01,
    TRAINING_ZONE = 0x02,
    DUMMY = 0x03
};

namespace MapConstants {
    constexpr uint8_t DUST    = static_cast<uint8_t>(MapType::DUST);
    constexpr uint8_t AZTEC_VILLAGE   = static_cast<uint8_t>(MapType::AZTEC_VILLAGE);
    constexpr uint8_t TRAINING_ZONE   = static_cast<uint8_t>(MapType::TRAINING_ZONE);
    constexpr uint8_t DUMMY           = static_cast<uint8_t>(MapType::DUMMY);
}
