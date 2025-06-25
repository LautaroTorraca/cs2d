

#ifndef READER_H
#define READER_H
#include <cstdint>
#include <string>

#include "common/DTO/DropInformation.h"
#include "common/DTO/PlayerInformation.h"
#include "common/Constants/SnapshotConstants.h"
#include "common/socket.h"

class Reader {
    Socket& socket;

    void bytesChecker(const int& bytesRead) const;

public:
    explicit Reader(Socket& socket);
    ~Reader() = default;

    [[nodiscard]] uint8_t u8tReader() const;

    uint16_t u16tReader() const;

    [[nodiscard]] std::string stringReader() const;
    std::vector<char> bytesReader() const;

    [[nodiscard]] double doubleRead() const;

    size_t readSizeT() const;

    int readInt() const;

    CoordinateInformation readCoordinateInformation() const;

    ProjectileInformation readProjectile() const;

    WeaponInformation readWeapon() const;

    PlayerInformation readPlayer() const;

    DropInformation readDrop() const;

    std::map<ProductType, double> readShopInfo() const;

    Snapshot readSnapShot() const;
};



#endif //READER_H
