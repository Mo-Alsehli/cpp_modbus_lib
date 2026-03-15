#include "modbus/function_codes/read_coils_handler.hpp"

CPDU CReadCoilsHandler::handle(const CPDU& request, CRegisterMap& registers) {
    auto data = request.get_data();

    if (data.size() != 4) {
        return request.exception(request.get_function_code(), 0x03);
    }

    uint16_t start_address = (data[0] << 8) | data[1];
    uint16_t coil_quantity = (data[2] << 8) | data[3];

    if (coil_quantity == 0 || coil_quantity > 2000) {
        return request.exception(request.get_function_code(), 0x03);
    }

    if (start_address + coil_quantity > registers.get_coil_count()) {
        return request.exception(request.get_function_code(), 0x02);
    }

    std::vector<uint8_t> response;

    response.push_back((coil_quantity + 7) / 8);

    for (uint16_t i = 0; i < response[0]; i++) {
        response.push_back(0);
    }

    for (uint16_t i = 0; i < coil_quantity; i++) {
        if (registers.read_coil(start_address + i)) {
            response[1 + (i / 8)] |= (1 << (i % 8));
        }
    }

    return CPDU(0x01, response);
}
