#pragma once

#include <memory>
#include <unordered_map>

#include "function_handler.hpp"

class CFunctionDispatcher {
   public:
    CFunctionDispatcher();

    CPDU process(const CPDU& request, CRegisterMap& registers);

   private:
    std::unordered_map<uint8_t, CIFunctionHandler> m_handlers;
};