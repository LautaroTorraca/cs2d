#include "SettingsParser.h"

#include <fstream>

#include <fkYAML/node.hpp>


#define SETTINGS "settings"

SettingsParser::SettingsParser(const std::string& gameInfoFilePath) {
    std::ifstream file(gameInfoFilePath.c_str());
    fkyaml::node root = fkyaml::node::deserialize(file);
    this->settings = root[SETTINGS].get_value<std::map<std::string, double>>();
}

SettingsParser::SettingsParser(SettingsParser&& other) noexcept: settings(other.settings) {
    if (this != &other) {
        other.settings = std::map<std::string, double>();
    }
}


double SettingsParser::getResolution(const std::string& key) const {
    if (this->settings.contains(key)) {
        return this->settings.at(key);
    }
    return 0;
}
