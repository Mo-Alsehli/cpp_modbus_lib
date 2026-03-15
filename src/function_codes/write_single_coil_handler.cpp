#include "modbus/function_codes/write_single_coil_handler.hpp"

CPDU CWriteSingleCoilHandler::handle(const CPDU& request, CRegisterMap& registers) {
    auto data = request.get_data();

    if (data.size() != 4) {
        return request.exception(request.get_function_code(), 0x03);
    }

    uint16_t address = (data[0] << 8) | data[1];
    uint16_t value = (data[2] << 8) | data[3];

    if (address >= registers.get_coil_count()) {
        return request.exception(request.get_function_code(), 0x02);
    }

    if (value != 0xFF00 && value != 0x0000) {
        return request.exception(request.get_function_code(), 0x03);
    }

    registers.write_coil(address, value == 0xFF00);

    return request;
}
