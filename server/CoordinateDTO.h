//
// Created by lionel on 26/05/25.
//

#ifndef COORDINATEDTO_H
#define COORDINATEDTO_H

class  CoordinateDTO {
    double x;
    double y;
public:

    CoordinateDTO(const double& x, const double& y) : x(x), y(y) {}
    [[nodiscard]] const double& getX() const { return x; }
    [[nodiscard]] const double& getY() const { return y; }
};

#endif //COORDINATEDTO_H
