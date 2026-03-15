#pragma once

#include "modbus/core/function_handler.hpp"

class CWriteMultipleRegistersHandler : public CIFunctionHandler {
   public:
    CPDU handle(const CPDU& request, CRegisterMap& registers) override;
};
