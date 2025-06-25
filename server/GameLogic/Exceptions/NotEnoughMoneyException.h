//
// Created by lionel on 23/06/25.
//

#ifndef NOTENOUGHMONEYEXCEPTION_H
#define NOTENOUGHMONEYEXCEPTION_H

#include <stdexcept>
#include <string>

class NotEnoughMoneyException: public std::runtime_error {
public:
    NotEnoughMoneyException(const NotEnoughMoneyException&) = delete;
    NotEnoughMoneyException& operator=(const NotEnoughMoneyException&) = delete;
    NotEnoughMoneyException(NotEnoughMoneyException&&) noexcept = delete;
    NotEnoughMoneyException& operator=(NotEnoughMoneyException&&) noexcept = delete;
    explicit NotEnoughMoneyException(const std::string& message): runtime_error(message) {}
};

#endif //NOTENOUGHMONEYEXCEPTION_H
