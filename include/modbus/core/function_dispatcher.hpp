#pragma once

#include <memory>
#include <unordered_map>

#include "modbus/core/function_handler.hpp"

class CFunctionDispatcher {
   public:
    CFunctionDispatcher();

    CPDU process(const CPDU& request, CRegisterMap& registers);

   private:
    std::unordered_map<uint8_t, std::unique_ptr<CIFunctionHandler>> m_handlers;
};