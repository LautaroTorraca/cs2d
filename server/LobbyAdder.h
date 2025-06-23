//
// Created by lionel on 23/06/25.
//

#ifndef LOBBYADDER_H
#define LOBBYADDER_H

#include <string>
#include <map>
#include <vector>

class LobbyAdder {
    public:
    virtual ~LobbyAdder() = default;
    virtual void add (const std::string& gameName, const size_t& id, std::map<std::string, std::vector<size_t>>& lobbies) const = 0;
};

#endif //LOBBYADDER_H
