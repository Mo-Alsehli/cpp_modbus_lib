#pragma once

#include <cstdint>
#include <span>

#include "modbus_pdu.hpp"

class CADU {
   public:
    virtual ~CADU() = default;

    virtual size_t encode(const CPDU& pdu, std::span<uint8_t> buffer, uint8_t unit_id) const = 0;

    virtual CPDU decode(std::span<const uint8_t> data, uint8_t& unit_id) const = 0;
};
