//
// Created by lionel on 26/05/25.
//

#include "Position.h"

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
    Coordinate center = this->getCenter();
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

bool Position::operator<(const Position &other) const {
    return this->reference < other.reference && this->width == other.width && this->height == other.height;
}

bool Position::intersects(const Position &position) const {
    uint32_t xStart = this->reference.addingX(0);
    uint32_t yStart = this->reference.addingY(0);
    uint32_t xLimit = this->reference.addingX(this->width);
    uint32_t yLimit = this->reference.addingY(this->height);

    uint32_t positionXStart = position.reference.addingX(0);
    uint32_t positionYStart = position.reference.addingY(0);
    uint32_t positionXLimit = position.reference.addingX(position.width);
    uint32_t positionYLimit = position.reference.addingY(position.height);

    return !(xLimit < positionXStart ||
             xStart > positionXLimit ||
             yLimit < positionYStart ||
             yStart > positionYLimit);
}

bool Position::contains(const Coordinate &coordinate) const {
    return this->intersects(Position(coordinate,0,0));
}

CoordinateDTO Position::getPoint() const {
    return this->reference.getCenter(this->width, this->height).getInfo();
}
