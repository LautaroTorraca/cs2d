//
// Created by lionel on 26/05/25.
//

#ifndef POSITION_H
#define POSITION_H

#include <cstdint>

#include "Coordinate.h"

class Position {
    Coordinate reference;
    uint16_t width;
    uint16_t height;
    public:
    Position(): width(0), height(0) {}
    Position(const uint32_t& x, const uint32_t& y, const uint16_t& width, const uint16_t& height) : reference(x, y), width(width), height(height) {}
    Position(const Coordinate& reference, const uint16_t& width, const uint16_t& height) : width(width), height(height) {
        this->reference.update(reference);
    }
    Position(Position&& other) noexcept;
    Position& operator=(Position&& other) noexcept;
    [[nodiscard]] std::vector<Coordinate> getArea() const;
    friend Position operator+(const Position& a, const Position& b) {
        Position result;
        result.reference = std::move(a.reference + b.reference);
        result.width = a.width;
        result.height = a.height;
        return result;
    }
    friend Position operator+(const Position& a, const Coordinate& b) {
        Position result;
        result.reference = std::move(a.reference + b);
        result.width = a.width;
        result.height = a.height;
        return result;
    }
    void updateLocationTo(const Position& position);
    double getAngleTo(const Coordinate & coordinate) const;
    void updateTo(const Position & position);
    Coordinate getCenter() const;
    bool operator<(const Position& other) const;
    bool intersects(const Position & position) const;
    bool contains(const Coordinate& coordinate) const;
    CoordinateDTO getPoint() const;

};



#endif //POSITION_H
