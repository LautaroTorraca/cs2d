//
// Created by lionel on 03/06/25.
//

#ifndef POSITIONDTO_H
#define POSITIONDTO_H
struct PositionDTO {
    const double x;
    const double y;
    PositionDTO(const double& x, const double& y): x(x), y(y) {}
};

#endif  // POSITIONDTO_H
