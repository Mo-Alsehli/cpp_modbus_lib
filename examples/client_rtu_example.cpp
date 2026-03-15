#include <iostream>

#include "modbus/client/modbus_client.hpp"
#include "modbus/transport/serial_transport.hpp"
#include "modbus/transport/uart_linux_bytestream.hpp"

int main() {
    CUARTByteStream uart("/dev/pts/4");

    CRTUTransport transport(uart);

    CModbusClient client(transport);

    client.write_single_register(1, 999);

    auto values = client.read_holding_register(0, 3);

    for (auto v : values) {
        std::cout << "Register value: " << v << std::endl;
    }

    return 0;
}
