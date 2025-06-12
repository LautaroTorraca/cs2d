//
// Created by lionel on 12/05/25.
//

#ifndef COORDINATES_H
#define COORDINATES_H
#include <cstdint>
#include <vector>

#include "CoordinateDTO.h"

class Coordinate {
    double x;
    double y;

public:
    // Coordinate(Coordinate&) = delete;
    // Coordinate& operator=(const Coordinate&) = delete;
    void update(const Coordinate& coordinate);
    [[nodiscard]] Coordinate getDisplace(const Coordinate& otherCoordinate) const;
    bool operator==(const Coordinate& other) const;
    Coordinate operator*(const double& scalar) const;
    Coordinate getDirectionTo(const Coordinate& coordinate);
    double distanceTo(const Coordinate& coordinate) const;
    [[nodiscard]] Coordinate rotatedIn(double deviationAngle) const;
    [[nodiscard]] uint32_t addingX(const uint32_t& x) const;
    [[nodiscard]] uint32_t addingY(const uint32_t& y) const;
    Coordinate getCenter(uint16_t width, uint16_t height) const;
    double getAngleTo(const Coordinate& coordinate);
    Coordinate(Coordinate&& other) noexcept;
    Coordinate& operator=(Coordinate&& other) noexcept;
    Coordinate(const double& x, const double& y): x(x), y(y) {}
    Coordinate(): x(0), y(0) {}
    Coordinate& operator+=(Coordinate& coordinate);
    Coordinate& operator-=(Coordinate& coordinate);
    friend Coordinate operator+(const Coordinate& other, const Coordinate& another) {
        Coordinate coordinate(other.x + another.x, other.y + another.y);
        return coordinate;
    }
    bool operator<(const Coordinate& other) const;
    [[nodiscard]] Coordinate getSector() const;
    [[nodiscard]] std::vector<Coordinate> getQuadrant(const int& width, const int& height) const;

    [[nodiscard]] CoordinateDTO getInfo() const;
};


#endif  // COORDINATES_H
