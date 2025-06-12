#pragma once

#include <QString>
#include <map>
#include <cstdint>
#include "mocks/MapTypeMock.h"

class MapMapper {
public:
    MapMapper();

    QString toString(MapType map) const;
    MapType toMap(uint8_t rawId) const;

private:
    std::map<uint8_t, MapType> idToMap;
    std::map<MapType, QString> mapToName;
};
