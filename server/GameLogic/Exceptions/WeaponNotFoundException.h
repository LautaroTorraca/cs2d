//
// Created by lionel on 22/06/25.
//

#ifndef WEAPONNOTFOUNDEXCEPTION_H
#define WEAPONNOTFOUNDEXCEPTION_H

#include <stdexcept>
#include <string>

class WeaponNotFoundException: public std::runtime_error {
public:
    WeaponNotFoundException(const WeaponNotFoundException&) = delete;
    WeaponNotFoundException& operator=(const WeaponNotFoundException&) = delete;
    WeaponNotFoundException(WeaponNotFoundException&&) noexcept = delete;
    WeaponNotFoundException& operator=(WeaponNotFoundException&&) noexcept = delete;
    explicit WeaponNotFoundException(const std::string& message): runtime_error(message) {}
};



#endif //WEAPONNOTFOUNDEXCEPTION_H
