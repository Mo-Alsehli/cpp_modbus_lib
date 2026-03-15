#include <iostream>

#include "modbus/server/modbus_server.hpp"
#include "modbus/server/register_map.hpp"
#include "modbus/transport/serial_transport.hpp"
#include "modbus/transport/uart_linux_bytestream.hpp"

int main() {
    CUARTByteStream uart("/dev/pts/7");
    CRTUTransport transport(uart);

    CRegisterMap registers(8,   // coils
                           0,   // discrete inputs
                           10,  // holding registers
                           2    // input registers
    );

    registers.write_coil(0, true);
    registers.write_coil(1, false);
    registers.write_coil(2, true);
    registers.write_coil(3, true);
    registers.write_coil(4, false);
    registers.write_coil(5, false);
    registers.write_coil(6, true);
    registers.write_coil(7, false);

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
