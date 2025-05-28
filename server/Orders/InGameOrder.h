#pragma once

#include "Order.h"
#include "OrderType.h"
#include <map>
#include "../Constants/protocolContants.h"
#include "cmake-build-docker /_deps/sdl2_mixer-src/src/codecs/stb_vorbis/stb_vorbis.h"

class InGameOrder final : public Order {
    OrderType orderType;
    size_t playerId;
    uint16_t direction;
    uint16_t ammoAmount;
    uint8_t weaponInformation;

    std::map<uint8_t, OrderType> orderTranslator;

public:

    InGameOrder(const uint8_t& code, const size_t& playerId);
    InGameOrder(const uint8_t& code, const size_t& playerId ,const uint16_t& direction);
    InGameOrder(const uint8_t& code, const size_t& playerId, const uint8_t& weaponInformation);
    InGameOrder(const uint8_t& code, const size_t& playerId, const uint16_t& ammoAmount, const uint8_t& weaponInformation);
    InGameOrder(const uint8_t& code, const size_t& playerId, const uint16_t& direction, const uint16_t& ammoAmount, const uint8_t& weaponInformation);


    InGameOrder(InGameOrder&& other) noexcept;
    InGameOrder& operator=(InGameOrder&& other) noexcept;

    InGameOrder(const InGameOrder&) = delete;
    InGameOrder& operator=(const InGameOrder&) = delete;

    [[nodiscard]] const OrderType& getOrderType() const override;
    [[nodiscard]] const size_t& getPlayerId() const;
    [[nodiscard]] const uint16_t& getDirection() const;
    const uint16_t& getAmmoAmount() const;
    const uint8_t& getWeaponInformation() const;
};
