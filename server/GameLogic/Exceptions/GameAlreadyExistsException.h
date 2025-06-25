//
// Created by lionel on 23/06/25.
//

#ifndef GAMEALREADYEXISTSEXCEPTION_H
#define GAMEALREADYEXISTSEXCEPTION_H

#include <stdexcept>
#include <string>

class GameAlreadyExistsException: public std::runtime_error {
public:
    GameAlreadyExistsException(const GameAlreadyExistsException&) = delete;
    GameAlreadyExistsException& operator=(const GameAlreadyExistsException&) = delete;
    GameAlreadyExistsException(GameAlreadyExistsException&&) noexcept = delete;
    GameAlreadyExistsException& operator=(GameAlreadyExistsException&&) noexcept = delete;
    explicit GameAlreadyExistsException(const std::string& message): runtime_error(message) {}
};



#endif //GAMEALREADYEXISTSEXCEPTION_H
