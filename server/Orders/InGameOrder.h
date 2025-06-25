#pragma once

#include <cstdint>
#include <map>

#include "Constants/ProductType.h"
#include "server/Constants/Movement.h"

#include "Order.h"
#include "OrderType.h"

class InGameOrder final : public Order {
    OrderType orderType;
    size_t playerId;
    uint16_t direction;
    double angle;
    uint16_t amount;
    uint8_t weaponInformation;
    std::map<uint8_t, OrderType> orderTranslator;
    std::map<uint16_t, Movement> movementTranslator;
    std::map<uint8_t, ProductType> toProduct;
    std::pair<double, double> position;

public:
    InGameOrder(const uint8_t &code, const size_t &playerId);
    InGameOrder(const uint8_t& code, const size_t& playerId,
        const std::pair<double, double>& position);
    InGameOrder(const uint8_t &code, const size_t &playerId,
              const uint16_t &direction);
    InGameOrder(const uint8_t &code, const size_t &playerId,
              const uint8_t &weaponInformation);
    InGameOrder(const uint8_t& code, const size_t& playerId, const double& angle);
    InGameOrder(const uint8_t &code, const size_t &playerId,
              const uint16_t &amount, const uint8_t &weaponInformation);
    InGameOrder(const uint8_t& code, const size_t& playerId, const uint16_t& direction,
        const double& angle, const uint16_t& amount, const uint8_t& weaponInformation,
        const std::pair<double, double>& position);


    InGameOrder(InGameOrder &&other) noexcept;
    InGameOrder &operator=(InGameOrder &&other) noexcept;

    InGameOrder(const InGameOrder &) = delete;
    InGameOrder &operator=(const InGameOrder &) = delete;

    [[nodiscard]] const OrderType &getOrderType() const override;
    [[nodiscard]] const size_t &getPlayerId() const;
    [[nodiscard]] const Movement &getDirection() const;
    const uint16_t &getAmount() const;
    const uint8_t &getWeaponInformation() const;
    const ProductType &getProduct() const;
    const std::pair<double, double> &getPosition() const;
    const double &getAngle() const;
};
