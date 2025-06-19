#include "SkinTraslator.h"

SkinMapper::SkinMapper() {
    // ID → Skin enum
    idToSkinMap = {
            {0x00, PHOENIX},
            {0x01, L337_KREW},
            {0x02, ARCTIC_AVENGER},
            {0x03, GUERRILLA},
            {0x10, SEAL_FORCE},
            {0x11, GERMAN_GSG9},
            {0x12, UK_SAS},
            {0x13, FRENCH_GIGN}
    };

    skinToNameMap = {
            {PHOENIX, "Phoenix"},
            {L337_KREW, "L337 Krew"},
            {ARCTIC_AVENGER, "Arctic Avenger"},
            {GUERRILLA, "Guerrilla"},
            {SEAL_FORCE, "SEAL Force"},
            {GERMAN_GSG9, "German GSG-9"},
            {UK_SAS, "UK SAS"},
            {FRENCH_GIGN, "French GIGN"}
    };
}

Skin SkinMapper::toSkin(uint8_t rawId) const {
    auto it = idToSkinMap.find(rawId);
    if (it != idToSkinMap.end()) {
        return it->second;
    }
    return static_cast<Skin>(rawId);
}

QString SkinMapper::toString(Skin skin) const {
    auto it = skinToNameMap.find(skin);
    if (it != skinToNameMap.end()) {
        return it->second;
    }
    return QString("Unknown Skin (%1)").arg(static_cast<uint8_t>(skin));
}
