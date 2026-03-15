#include <iostream>

#include "modbus/server/modbus_server.hpp"
#include "modbus/server/register_map.hpp"
#include "modbus/transport/serial_transport.hpp"
#include "modbus/transport/uart_linux_bytestream.hpp"

int main() {
    CUARTByteStream uart("/dev/pts/3");
    CRTUTransport transport(uart);

    CRegisterMap registers(0,   // coils
                           0,   // discrete inputs
                           10,  // holding registers
                           0    // input registers
    );

    registers.write_holding_register(0, 100);
    registers.write_holding_register(1, 200);
    registers.write_holding_register(2, 300);

    CModbusServer server(transport, registers);

    std::cout << "Modbus RTU server started" << std::endl;

    while (true) {
        server.poll();
    }

    return 0;
}
