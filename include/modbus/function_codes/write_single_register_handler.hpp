#pragma once
#include "function_handler.hpp"

class CWriteSingleRegisterHandler : public CIFunctionHandler {
   public:
    CPDU handle(const CPDU& request, CRegisterMap& registers) override;
};