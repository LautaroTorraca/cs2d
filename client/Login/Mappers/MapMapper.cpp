#include "MapTraslator.h"

MapMapper::MapMapper() {
    idToMap = {
            {0x00, MapType::DUST},
            {0x01, MapType::AZTEC_VILLAGE},
            {0x02, MapType::TRAINING_ZONE}
    };

    mapToName = {
            {MapType::DUST, "Dust"},
            {MapType::AZTEC_VILLAGE, "Aztec Village"},
            {MapType::TRAINING_ZONE, "Training Zone"}
    };
}

MapType MapMapper::toMap(uint8_t rawId) const {
    auto it = idToMap.find(rawId);
    if (it != idToMap.end()) {
        return it->second;
    }
    return MapType::DUMMY;
}

QString MapMapper::toString(MapType map) const {
    auto it = mapToName.find(map);
    if (it != mapToName.end()) {
        return it->second;
    }
    return QString("Unknown Map (%1)").arg(static_cast<uint8_t>(map));
}
