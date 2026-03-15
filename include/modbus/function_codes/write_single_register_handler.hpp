#pragma once
#include "modbus/core/function_handler.hpp"

class CWriteSingleRegisterHandler : public CIFunctionHandler {
   public:
    CPDU handle(const CPDU& request, CRegisterMap& registers) override;
};