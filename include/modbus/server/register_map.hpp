#pragma once

#include <cstdint>
#include <vector>

class CRegisterMap {
   public:
    CRegisterMap(size_t coils_count, size_t discrete_input_count, size_t holding_register_count, size_t input_registers_count);

    bool read_coil(uint16_t address) const;
    void write_coil(uint16_t address, bool value);
    size_t get_coil_count() const;

    bool read_discrete_input(uint16_t address) const;
    size_t get_discrete_input_count() const;

    uint16_t read_holding_register(uint16_t address) const;
    void write_holding_register(uint16_t address, uint16_t value);
    size_t get_holding_register_count() const;

    uint16_t read_input_register(uint16_t address) const;
    size_t get_input_register_count() const;

   private:
    std::vector<bool> m_coils;
    std::vector<bool> m_discrete_input;
    std::vector<uint16_t> m_holding_registers;
    std::vector<uint16_t> m_input_registers;
};
