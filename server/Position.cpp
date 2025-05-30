//
// Created by lionel on 26/05/25.
//

#include "Position.h"

#include "GameMap.h"

Position::Position(Position &&other) noexcept : reference(std::move(other.reference)), width(other.width), height(other.height) {
    if (this != &other) {
        other.reference = std::move(Coordinate());
        other.width = 0;
        other.height = 0;
    }
}

std::vector<Coordinate> Position::getArea() const {
    return this->reference.getQuadrant(this->width, this->height);
}

Position & Position::operator=(Position &&b) noexcept {
    if (this != &b) {
        this->reference = std::move(b.reference);
        this->width = b.width;
        this->height = b.height;
        b.reference = std::move(Coordinate());
        b.width = 0;
        b.height = 0;
    }
    return *this;
}

void Position::updateLocationTo(const Position &position) {
    this->reference.update(position.reference);
    this->width = position.width;
    this->height = position.height;
}

double Position::getAngleTo(const Coordinate &coordinate) const {
    Coordinate center = this->reference.getCenter(this->width, this->height);
    return center.getAngleTo(coordinate);
}

void Position::updateTo(const Position &position) {
    this->reference.update(position.reference);
    this->width = position.width;
    this->height = position.height;
}

Coordinate Position::getCenter() const {
    return this->reference.getCenter(this->width, this->height);
}

CoordinateDTO Position::getPoint() const {
    return this->reference.getCenter(this->width, this->height).getInfo();
}
