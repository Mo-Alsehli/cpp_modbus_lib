#pragma once

#include "function_dispatcher.hpp"
#include "modbus_pdu.hpp"
#include "register_map.hpp"
#include "transport.hpp"

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