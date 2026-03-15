#pragma once

#include "modbus/core/function_dispatcher.hpp"
#include "modbus/core/modbus_pdu.hpp"
#include "modbus/server/register_map.hpp"
#include "modbus/transport/transport.hpp"

class CModbusServer {
   public:
    CModbusServer(CTransport& transport, CRegisterMap& registers);

    void poll();

   private:
    CTransport& m_transport;
    CRegisterMap& m_registers;
    CFunctionDispatcher m_dispatcher;

    std::vector<uint8_t> m_rx_buffer;
    std::vector<uint8_t> m_tx_buffer;
};