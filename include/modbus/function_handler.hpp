#pragma once

#include "modbus_pdu.hpp"
#include "register_map.hpp"

class CIFunctionHandler {
   public:
    virtual ~CIFunctionHandler() = default;

    virtual CPDU handle(const CPDU& request, CRegisterMap& registers) = 0;
};