#pragma once

#include <QString>
#include <cstdint>
#include <map>

#include "common/Constants/Skin.h"

class SkinMapper {
private:
    std::map<uint8_t, Skin> idToSkinMap;
    std::map<Skin, QString> skinToNameMap;

public:
    SkinMapper();

    Skin toSkin(uint8_t rawId) const;
    QString toString(Skin skin) const;
    uint8_t toSkinId(const QString& skinName) const;


};
