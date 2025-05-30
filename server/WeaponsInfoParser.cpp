//
// Created by lionel on 28/05/25.
//

#include "WeaponsInfoParser.h"
#include <fstream>
#include <iostream>
#include <ranges>

#define KNIFE_KEY "knife"
#define GLOCK_KEY "glock"
#define AK_KEY "ak47"
#define M3_KEY "m3"
#define AWP_KEY "awp"

WeaponsInfoParser::WeaponsInfoParser(const std::string& weaponsFilePath) {

    std::ifstream file(weaponsFilePath.c_str());
    fkyaml::node root = fkyaml::node::deserialize(file);
    this->fillWeaponTranslator();
    for ( auto& key : this->getRootKeysAlt(root) ) {
        if ( this->weaponsTranslator.contains(key) ) {
            auto infos = root[key].get_value<std::map<std::string, double>>();
            this->weaponsInfo.emplace(this->weaponsTranslator.at(key), infos);
        }
    }

}

WeaponsInfoParser::WeaponsInfoParser(WeaponsInfoParser &&other) noexcept :
                                    weaponsInfo(std::move(other.weaponsInfo)),
                                    weaponsTranslator(std::move(other.weaponsTranslator)) {
    other.weaponsInfo = std::map<WeaponType, std::map<std::string, double>>();
    other.weaponsTranslator = std::map<std::string, WeaponType>();
}

double WeaponsInfoParser::getWeaponInfo(const WeaponType &type, const std::string &info) const {
    if ( !this->weaponsInfo.contains(type) ) return 0;
    if ( !this->weaponsInfo.at(type).contains(info) ) return 0;
    return this->weaponsInfo.at(type).at(info);
}

std::vector<std::string> WeaponsInfoParser::getRootKeysAlt(const fkyaml::node& root) {
    std::vector<std::string> keys;

    for (const auto &key: root.as_map() | std::views::keys) {
        keys.push_back(key.get_value<std::string>());
    }

    return keys;
}

void WeaponsInfoParser::fillWeaponTranslator() {
    this->weaponsTranslator.emplace(KNIFE_KEY, WeaponType::KNIFE);
    this->weaponsTranslator.emplace(GLOCK_KEY, WeaponType::GLOCK);
    this->weaponsTranslator.emplace(AK_KEY, WeaponType::AK47);
    this->weaponsTranslator.emplace(M3_KEY, WeaponType::M3);
    this->weaponsTranslator.emplace(AWP_KEY, WeaponType::AWP);

}
