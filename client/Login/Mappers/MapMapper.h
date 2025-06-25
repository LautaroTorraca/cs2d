#pragma once

#include <QString>
#include <cstdint>
#include <map>
#include <vector>

#include "common/Constants/MapTypeConstants.h"

class MapMapper {
private:
    std::map<uint8_t, MapType> idToMap;
    std::map<MapType, uint8_t> mapToId;
    std::map<MapType, QString> mapToName;

public:
    MapMapper();

    QString toString(MapType map) const;
    MapType toMap(uint8_t rawId) const;
    uint8_t toRawId(MapType map) const;
    std::vector<MapType> getAvailableMaps() const;

};
