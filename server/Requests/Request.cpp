#include "Request.h"

Request::Request(const size_t& id, std::map<std::string, std::vector<char>>& metaData)
    : id(id), metaData(std::move(metaData)) {}

Request::Request(Request&& other) noexcept: id(other.id), metaData(std::move(other.metaData)) {
    if (this == &other) {
        return;
    }
    other.id = 0;
    other.metaData = std::map<std::string, std::vector<char>>();
}

Request& Request::operator=(Request&& other) noexcept {
    if (this == &other) {
        return *this;
    }
    this->id = other.id;
    this->metaData = std::move(other.metaData);
    other.id = 0;
    other.metaData = std::map<std::string, std::vector<char>>();
    return *this;
}

const size_t& Request::getId() const { return this->id; }

std::map<std::string, std::vector<char>> Request::getRequest() const { return this->metaData; }
