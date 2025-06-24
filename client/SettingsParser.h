#pragma once
#include <map>
#include <string>

class SettingsParser {
    std::map<std::string, double> settings;

public:
    explicit SettingsParser(const std::string& gameInfoFilePath);
    SettingsParser(SettingsParser&& other) noexcept;
    double getResolution(const std::string& key) const;
};
