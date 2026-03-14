#include "modbus_pdu.hpp"

uint8_t CPDU::get_function_code() const { return m_function_code; }

std::span<const uint8_t> CPDU::get_data() const { return m_data; }

bool CPDU::is_exception() const { return m_function_code & 0x80; }

uint8_t CPDU::exception_code() const {
    if (!is_exception()) {
        std::cerr << "[ERROR] Not An EXCEPTION Response" << std::endl;
        return 1;
    }

    return m_data[0];
}

CPDU CPDU::exception(uint8_t fc, uint8_t code) const { return CPDU(fc | 0x80, {code}); }

size_t CPDU::serialize(std::span<uint8_t> buffer) const {
    size_t required_size = m_data.size() + 1;

    if (buffer.size() < required_size) {
        std::cerr << "[ERROR] Small Buffer Size" << std::endl;
        return -1;
    }

    buffer[0] = m_function_code;

    std::copy(m_data.begin(), m_data.end(), buffer.begin() + 1);

    return required_size;
}

CPDU CPDU::parse(std::span<uint8_t> bytes) {
    if (bytes.size() < 1) {
        std::cerr << "[ERROR] Invalid Bytes Size" << std::endl;
    }

    uint8_t function_code = bytes[0];

    std::vector<uint8_t> data(bytes.begin() + 1, bytes.end());

    return CPDU(function_code, std::move(data));
}
