#include "write_single_register_handler.hpp"

CPDU CWriteSingleRegisterHandler::handle(const CPDU& request, CRegisterMap& registers) {
    auto data = request.get_data();

    if (data.size() != 4) {
        return request.exception(request.get_function_code(), 0x03);
    }

    uint16_t address = (data[0] << 8) | data[1];
    uint16_t value = (data[2] << 8) | data[3];

    if (address >= registers.get_holding_register_count()) {
        return request.exception(request.get_function_code(), 0x02);
    }

    registers.write_holding_register(address, value);

    return request;
}