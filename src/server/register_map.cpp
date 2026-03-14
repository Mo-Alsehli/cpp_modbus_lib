#include "register_map.hpp"

CRegisterMap::CRegisterMap(size_t coils_count, size_t discrete_input_count, size_t holding_register_count, size_t input_registers_count)
    : m_coils(coils_count, 0),
      m_discrete_input(discrete_input_count, 0),
      m_holding_registers(holding_register_count, 0),
      m_input_registers(input_registers_count, 0) {}

bool CRegisterMap::read_coil(uint16_t address) const { return m_coils.at(address); }
void CRegisterMap::write_coil(uint16_t address, bool value) { m_coils.at(address) = value; }
size_t CRegisterMap::get_coil_count() const { return m_coils.size(); }

bool CRegisterMap::read_discrete_input(uint16_t address) const { return m_discrete_input.at(address); }
size_t CRegisterMap::get_discrete_input_count() const { return m_discrete_input.size(); }

uint16_t CRegisterMap::read_holding_register(uint16_t address) const { return m_holding_registers.at(address); }
void CRegisterMap::write_holding_register(uint16_t address, uint16_t value) { m_holding_registers.at(address) = value; }
size_t CRegisterMap::get_holding_register_count() const { return m_holding_registers.size(); }

uint16_t CRegisterMap::read_input_register(uint16_t address) const { return m_input_registers.at(address); }
size_t CRegisterMap::get_input_register_count() const { return m_input_registers.size(); }