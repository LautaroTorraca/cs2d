//
// Created by lionel on 28/05/25.
//

#ifndef WEAPONSINFOPARSER_H
#define WEAPONSINFOPARSER_H
#include <map>
#include <string>
#include <fkYAML/node.hpp>
#include "WeaponConstants.h"
#include "WeaponInformer.h"

class WeaponsInfoParser : public WeaponInformer {
    std::map<WeaponType, std::map<std::string, double>> weaponsInfo;
    std::map<std::string, WeaponType> weaponsTranslator;
    std::vector<std::string> getRootKeysAlt(const fkyaml::node &root);
    void fillWeaponTranslator();
public:
    explicit WeaponsInfoParser(const std::string& weaponsFilePath);
    WeaponsInfoParser(WeaponsInfoParser&& other) noexcept;
    [[nodiscard]] double getWeaponInfo(const WeaponType& type, const std::string& info) const override;

};



#endif //WEAPONSINFOPARSER_H
