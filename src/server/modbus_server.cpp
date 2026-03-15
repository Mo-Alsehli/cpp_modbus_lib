#include "modbus/server/modbus_server.hpp"

CModbusServer::CModbusServer(CTransport& transport, CRegisterMap& registers)
    : m_transport(transport), m_registers(registers), m_rx_buffer(256), m_tx_buffer(256) {}

void CModbusServer::poll() {
    size_t received;

    auto err = m_transport.receive(m_rx_buffer, received);

    if (err != ETransportError::None) {
        return;
    }

    auto pdu = CPDU::parse(std::span<uint8_t>(m_rx_buffer.data(), received));

    CPDU response = m_dispatcher.process(pdu, m_registers);

    size_t size = response.serialize(m_tx_buffer);

    m_transport.send(std::span<uint8_t>(m_tx_buffer.data(), size));
}
