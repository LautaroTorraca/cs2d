//
// Created by lionel on 28/05/25.
//

#ifndef GLOCK_H
#define GLOCK_H
#include "Weapon.h"
#include "Projectile.h"

#define GLOCK_INITIAL_AMMO 30

class Glock : public Weapon {
    uint16_t ammo;
    double glockDamagePerBullet;
    double glockPrecision;
    double glockRange;
    double glockCadence;
    double glockSpeed;
    double glockBulletsPerShot;
    double lastShotTime;
    std::vector<Projectile> projectiles;
    public:
    Glock(const double& glockDamagePerBullet, const double& glockPrecision, const double& glockRange, const double& glockCadence, const double& glockSpeed, const double& glockBulletsPerShot) :
    ammo(GLOCK_INITIAL_AMMO),
    glockDamagePerBullet(glockDamagePerBullet),
    glockPrecision(glockPrecision),
    glockRange(glockRange),
    glockCadence(glockCadence),
    glockSpeed(glockSpeed),
    glockBulletsPerShot(glockBulletsPerShot),
    lastShotTime(0) {}
    void attack(Positionable &positionable, const Position &actualPosition, const Coordinate &destination) override;
    void recharge(uint16_t &amount) override;
    WeaponInfoDTO getInfo() override;

};



#endif //GLOCK_H
