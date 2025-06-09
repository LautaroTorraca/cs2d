//
// Created by lionel on 03/06/25.
//

#ifndef COORDINATEINFORMATION_H
#define COORDINATEINFORMATION_H
struct CoordinateInformation {
    double x;
    double y;
    CoordinateInformation() = default;
    CoordinateInformation(const double& x, const double& y): x(x), y(y) {}
};
#endif  // COORDINATEINFORMATION_H
