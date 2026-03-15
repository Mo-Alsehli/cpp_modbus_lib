#pragma once

#include "modbus/core/function_handler.hpp"

class CReadCoilsHandler : public CIFunctionHandler {
   public:
    CPDU handle(const CPDU& request, CRegisterMap& registers) override;
};
