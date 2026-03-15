#include <iostream>

#include "modbus/client/modbus_client.hpp"
#include "modbus/core/modbus_pdu.hpp"
#include "modbus/transport/serial_transport.hpp"
#include "modbus/transport/uart_linux_bytestream.hpp"

int main() {
    CUARTByteStream uart("/dev/pts/6");

    CRTUTransport transport(uart);

    CModbusClient client(transport);

    auto send_request = [&](const CPDU& request) {
        std::vector<uint8_t> buffer(256);

        size_t size = request.serialize(buffer);

        transport.send({buffer.data(), size});

        size_t received;

        transport.receive(buffer, received);

        return CPDU::parse({buffer.data(), received});
    };

    auto read_coils_response = send_request(CPDU(0x01, {0x00, 0x00, 0x00, 0x08}));
    auto read_coils_data = read_coils_response.get_data();

    std::cout << "Read coils byte count: " << static_cast<int>(read_coils_data[0]) << std::endl;
    std::cout << "Read coils data: " << static_cast<int>(read_coils_data[1]) << std::endl;

    auto read_input_registers_response = send_request(CPDU(0x04, {0x00, 0x00, 0x00, 0x02}));
    auto read_input_registers_data = read_input_registers_response.get_data();

    for (size_t i = 1; i < read_input_registers_data.size(); i += 2) {
        uint16_t value = (read_input_registers_data[i] << 8) | read_input_registers_data[i + 1];
        std::cout << "Input register value: " << value << std::endl;
    }

    auto write_single_coil_response = send_request(CPDU(0x05, {0x00, 0x03, 0xFF, 0x00}));
    auto write_single_coil_data = write_single_coil_response.get_data();

    std::cout << "Write single coil address: " << ((write_single_coil_data[0] << 8) | write_single_coil_data[1]) << std::endl;
    std::cout << "Write single coil value: " << ((write_single_coil_data[2] << 8) | write_single_coil_data[3]) << std::endl;

    client.write_single_register(1, 999);
    send_request(CPDU(0x10, {0x00, 0x01, 0x00, 0x02, 0x04, 0x00, 0x64, 0x00, 0xC8}));

    auto values = client.read_holding_register(0, 3);

    for (auto v : values) {
        std::cout << "Register value: " << v << std::endl;
    }

    return 0;
}
