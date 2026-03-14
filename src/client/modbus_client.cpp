#include "modbus_client.hpp"

CModbusClient::CModbusClient(CTransport& transport) : m_transport(transport) {}

std::vector<uint16_t> CModbusClient::read_holding_register(uint16_t start_address, uint16_t qunatity) {
    std::vector<uint8_t> req;

    req.push_back(start_address >> 8);
    req.push_back(start_address & 0xFF);

    req.push_back(qunatity >> 8);
    req.push_back(qunatity & 0xFF);

    std::vector<uint8_t> buffer(256);
    CPDU request(0x03, req);

    size_t size = request.serialize(buffer);

    m_transport.send({buffer.data(), size});

    size_t received;

    m_transport.receive(buffer, received);

    CPDU response = CPDU::parse({buffer.data(), received});

    if (response.is_exception()) {
        std::cerr << "[ERROR] modbuse Exception with code: " << response.exception_code() << std::endl;
        return {0};
    }

    auto data = response.get_data();

    std::vector<uint16_t> result;

    for (size_t i = 1; i < data.size(); i += 2) result.push_back((data[i] << 8) | data[i + 1]);

    return result;
}

void CModbusClient::write_single_register(uint16_t address, uint16_t value) {
    std::vector<uint8_t> req;

    req.push_back(address >> 8);
    req.push_back(address & 0xFF);

    req.push_back(value >> 8);
    req.push_back(value & 0xFF);

    std::vector<uint8_t> buffer(256);
    CPDU request(0x06, req);

    size_t size = request.serialize(buffer);

    m_transport.send({buffer.data(), size});

    size_t received;

    m_transport.receive(buffer, received);

    CPDU response = CPDU::parse({buffer.data(), received});

    if (response.is_exception()) {
        std::cerr << "[ERROR] modbuse Exception with code: " << response.exception_code() << std::endl;
        return;
    }
}