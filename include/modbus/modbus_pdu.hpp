#include <cstdint>
#include <iostream>
#include <span>
#include <vector>

class CPDU {
   public:
    CPDU(uint8_t funciton_code, std::vector<uint8_t> data) : m_function_code(funciton_code), m_data(data) {}

    uint8_t get_function_code() const;

    std::span<const uint8_t> get_data() const;

    bool is_exception() const;

    uint8_t exception_code() const;

    size_t serialize(std::span<uint8_t> buffer) const;

    static CPDU parse(std::span<uint8_t> bytes);

   private:
    uint8_t m_function_code;
    std::vector<uint8_t> m_data;
};