#include "modbus/function_codes/write_multiple_registers_handler.hpp"

CPDU CWriteMultipleRegistersHandler::handle(const CPDU& request, CRegisterMap& registers) {
    auto data = request.get_data();

    if (data.size() < 5) {
        return request.exception(request.get_function_code(), 0x03);
    }

    uint16_t start_address = (data[0] << 8) | data[1];
    uint16_t reg_quantity = (data[2] << 8) | data[3];
    uint8_t byte_count = data[4];

    if (reg_quantity == 0 || reg_quantity > 123 || byte_count != reg_quantity * 2) {
        return request.exception(request.get_function_code(), 0x03);
    }

    if (data.size() != static_cast<size_t>(5 + byte_count)) {
        return request.exception(request.get_function_code(), 0x03);
    }

    if (start_address + reg_quantity > registers.get_holding_register_count()) {
        return request.exception(request.get_function_code(), 0x02);
    }

    for (uint16_t i = 0; i < reg_quantity; i++) {
        uint16_t value = (data[5 + (i * 2)] << 8) | data[6 + (i * 2)];
        registers.write_holding_register(start_address + i, value);
    }

    return CPDU(0x10, {data[0], data[1], data[2], data[3]});
}
