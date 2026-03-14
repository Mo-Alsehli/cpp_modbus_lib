#pragma once

#include "function_handler.hpp"

class CReadHoldingRegisterHandler : public CIFunctionHandler {
   public:
    CPDU handle(const CPDU& request, CRegisterMap& registers) override;
};