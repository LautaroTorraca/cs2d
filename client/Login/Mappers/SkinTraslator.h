#pragma once

#include <QString>
#include <map>
#include <cstdint>
#include "server/Skin.h"

class SkinMapper {
public:
    SkinMapper();

    Skin toSkin(uint8_t rawId) const;
    QString toString(Skin skin) const;

private:
    std::map<uint8_t, Skin> idToSkinMap;
    std::map<Skin, QString> skinToNameMap;
};
