//
// Created by lionel on 23/06/25.
//

#ifndef ORDERNOTIMPLEMENTEDEXCEPTION_H
#define ORDERNOTIMPLEMENTEDEXCEPTION_H

#include <stdexcept>
#include <string>

class OrderNotImplementedException: public std::runtime_error {
public:
    OrderNotImplementedException(const OrderNotImplementedException&) = delete;
    OrderNotImplementedException& operator=(const OrderNotImplementedException&) = delete;
    OrderNotImplementedException(OrderNotImplementedException&&) noexcept = delete;
    OrderNotImplementedException& operator=(OrderNotImplementedException&&) noexcept = delete;
    explicit OrderNotImplementedException(const std::string& message): runtime_error(message) {}
};

#endif //ORDERNOTIMPLEMENTEDEXCEPTION_H
