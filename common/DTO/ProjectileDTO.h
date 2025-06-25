//
// Created by lionel on 30/05/25.
//

#ifndef PROJECTILEDTO_H
#define PROJECTILEDTO_H
#include "DTO/CoordinateDTO.h"


class ProjectileDTO {
    CoordinateDTO coordinateDTO;
    public:
    explicit ProjectileDTO(const CoordinateDTO& coordinateDTO) : coordinateDTO(coordinateDTO) {}
    [[nodiscard]] const CoordinateDTO& getCoordinateDTO() const;

};



#endif //PROJECTILEDTO_H
