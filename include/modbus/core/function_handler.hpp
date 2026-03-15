#pragma once

#include "modbus/core/modbus_pdu.hpp"
#include "modbus/server/register_map.hpp"

class CIFunctionHandler {
   public:
    virtual ~CIFunctionHandler() = default;

    virtual CPDU handle(const CPDU& request, CRegisterMap& registers) = 0;
};