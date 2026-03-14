#include "read_holding_register_handler.hpp"

CPDU CReadHoldingRegisterHandler::handle(const CPDU& request, CRegisterMap& registers) {
    auto data = request.get_data();

    if (data.size() != 4) {
        return request.exception(request.get_function_code(), 0x03);
    }

    uint16_t start_address = (data[0] << 8) | data[1];
    uint16_t reg_quantity = (data[2] << 8) | data[3];

    if (reg_quantity == 0 || reg_quantity > 125) {
        return request.exception(request.get_function_code(), 0x03);
    }

    if (start_address + reg_quantity > registers.get_holding_register_count()) {
        return request.exception(request.get_function_code(), 0x02);
    }

    std::vector<uint8_t> response;

    response.push_back(reg_quantity * 2);

    for (uint16_t i = 0; i < reg_quantity; i++) {
        uint16_t value = registers.read_holding_register(start_address + i);
        response.push_back(value >> 8);
        response.push_back(value & 0xFF);
    }

    return CPDU(0x03, response);
}