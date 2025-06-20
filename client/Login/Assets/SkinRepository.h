#pragma once

#include <QString>
#include <QVector>
#include <cstdint>

struct SkinInfo {
    QString name;
    QString resourcePath;
    QString fallbackPath;
    uint8_t skinId;
};

class SkinRepository {
public:
    static QVector<SkinInfo> getSkinsForTeam(uint8_t teamId);
};
