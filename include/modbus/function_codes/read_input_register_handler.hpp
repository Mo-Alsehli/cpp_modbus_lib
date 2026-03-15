#pragma once

#include "modbus/core/function_handler.hpp"

class CReadInputRegisterHandler : public CIFunctionHandler {
   public:
    CPDU handle(const CPDU& request, CRegisterMap& registers) override;
};
