#include "function_dispatcher.hpp"

#include "read_holding_register_handler.hpp"
#include "write_single_register_handler.hpp"

CFunctionDispatcher::CFunctionDispatcher() {
    m_handlers[0x03] = std::make_unique<CReadHoldingRegisterHandler>();
    m_handlers[0x06] = std::make_unique<CWriteSingleRegisterHandler>();
}

CPDU CFunctionDispatcher::process(const CPDU& request, CRegisterMap& registers) {
    uint8_t fc = request.get_function_code();

    auto it = m_handlers.find(fc);

    if (it == m_handlers.end()) {
        return request.exception(request.get_function_code(), {0x1});
    }

    return it->second->handle(request, registers);
}