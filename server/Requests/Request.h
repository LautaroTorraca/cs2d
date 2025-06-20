
#ifndef REQUEST_H
#define REQUEST_H
#include <map>
#include <string>
#include <vector>

class Request {
    size_t id;
    std::map<std::string, std::vector<char>> metaData;

public:
    Request(const Request&) = delete;
    Request& operator=(const Request&) = delete;

    Request(Request&& other) noexcept;
    Request& operator=(Request&& other) noexcept;

    Request(const size_t& id, std::map<std::string, std::vector<char>>& metaData);
    explicit Request(const size_t& id) : id(id) {}
    [[nodiscard]] const size_t& getId() const;
    [[nodiscard]] std::map<std::string, std::vector<char>> getRequest() const;
};


#endif  // REQUEST_H
