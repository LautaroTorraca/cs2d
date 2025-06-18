//
// Created by lionel on 12/05/25.
//

#include "Coordinate.h"

#include <tuple>
#include <cmath>

#define TILE_SIZE 32 //TODO: Esto debera ser reemplazado por la medida que se termine usando
#define PI_IN_GRADES 180

void Coordinate::update(const Coordinate &coordinate) {
    this->x = coordinate.x;
    this->y = coordinate.y;
}

Coordinate Coordinate::getDisplace(const Coordinate &otherCoordinate) const {
    Coordinate displace;
    displace.x = otherCoordinate.x - this->x;
    displace.y = otherCoordinate.y - this->y;
    return displace;
}

bool Coordinate::operator==(const Coordinate &other) const {
    return this->x == other.x && this->y == other.y;
}

Coordinate Coordinate::operator*(const double& scalar) const {
    Coordinate newCoordinate(this->x * scalar, this->y * scalar);
    return newCoordinate;
}

Coordinate Coordinate::getDirectionTo(const Coordinate &coordinate) {
    Coordinate direction;
    direction.x = coordinate.x - this->x;
    direction.y = coordinate.y - this->y;
    double distance = this->distanceTo(coordinate);
    direction.x /= distance;
    direction.y /= distance;
    return direction;
}

double Coordinate::distanceTo(const Coordinate &coordinate) const {
    return std::sqrt(std::pow(this->x - coordinate.x, 2) + std::pow(this->y - coordinate.y, 2));
}

Coordinate Coordinate::rotatedIn(double deviationAngle) const {
    double norm = sqrt(this->x * this->x + this->y * this->y);
    double angle = std::atan2(this->y, this->x);
    angle += (deviationAngle*M_PI)/PI_IN_GRADES;
    double rotatedX = std::cos(angle);
    double rotatedY = std::sin(angle);
    rotatedX *= norm;
    rotatedY *= norm;
    return Coordinate(rotatedX, rotatedY);
}

uint32_t Coordinate::addingX(const uint32_t& x) const {
    return  this->x + x;
}

uint32_t Coordinate::addingY(const uint32_t& y) const {
    return  this->y + y;
}

Coordinate Coordinate::getCenter(uint16_t width, uint16_t height) const {
    return Coordinate(this->x + width / 2, this->y + height / 2);
}

double Coordinate::getAngleTo(const Coordinate &coordinate) {
    double relativeX = coordinate.x - this->x;
    double relativeY = coordinate.y - this->y;
    return std::atan2(relativeY, relativeX);
}

Coordinate::Coordinate(Coordinate &&other) noexcept : x(other.x), y(other.y) {
    if (this == &other) {
        return;
    }
    other.x = 0;
    other.y = 0;
}

Coordinate& Coordinate::operator=(Coordinate &&other) noexcept {
    if (this == &other) {
        return *this;
    }
    this->x = other.x;
    this->y = other.y;
    other.x = 0;
    other.y = 0;
    return *this;
}

Coordinate& Coordinate::operator+=(Coordinate& coordinate){
    this->x += coordinate.x;
    this->y += coordinate.y;
    return *this;
}

Coordinate& Coordinate::operator-=(Coordinate& coordinate){
    this->x -= coordinate.x;
    this->y -= coordinate.y;
    return *this;
}

bool Coordinate::operator<(const Coordinate &other) const {
    int otherX = other.x;
    int otherY = other.y;
    int x = this->x;
    int y = this->y;
    return std::tie(x, y) < std::tie(otherX, otherY);
}

Coordinate Coordinate::getSector() const {
    int xQuadrant = this->x;
    xQuadrant /= TILE_SIZE;
    int yQuadrant = this->y;
    yQuadrant /= TILE_SIZE;
    return Coordinate(xQuadrant, yQuadrant);
}

std::vector<Coordinate> Coordinate::getQuadrant(const int& width, const int& height) const {
    std::vector<Coordinate> quadrant;
    for (int i = this->x; i < width + this->x; i++) {
        for (int j = this->y; j < height + this->y; j++) {
            quadrant.emplace_back(i, j);
        }
    }
    return quadrant;
}

CoordinateDTO Coordinate::getInfo() const {
    return {this->x, this->y};
}
