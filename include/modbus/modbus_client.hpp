#pragma once

#include <cstdint>

#include "modbus_pdu.hpp"
#include "transport.hpp"

class CModbusClient {
   public:
    CModbusClient(CTransport& transport);

    std::vector<uint16_t> read_holding_register(uint16_t start_address, uint16_t qunatity);
    void write_single_register(uint16_t address, uint16_t value);

   private:
    CTransport& m_transport;
};
