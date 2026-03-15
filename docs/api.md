# API Documentation

This page describes the public library API in simple words.

## Main Parts

The library has four main parts:

- Transport
- PDU
- Server
- Client

It also has a register map used by the server.

## Transport API

File: [include/modbus/transport/transport.hpp](/home/mmagdi/workspace/modbus_lib/include/modbus/transport/transport.hpp)

`CTransport` is the base transport interface.

### `ETransportError`

Possible transport results:

- `None`
- `Timeout`
- `Disconnected`
- `WriteError`
- `IOError`

### `class CTransport`

#### `virtual ETransportError connect() = 0;`

Opens or prepares the transport.

#### `virtual void close() = 0;`

Closes the transport.

#### `virtual ETransportError send(std::span<const uint8_t> data) = 0;`

Sends bytes.

#### `virtual ETransportError receive(std::span<uint8_t> data, size_t& received) = 0;`

Receives bytes and writes the received size into `received`.

## RTU Serial Transport

File: [include/modbus/transport/serial_transport.hpp](/home/mmagdi/workspace/modbus_lib/include/modbus/transport/serial_transport.hpp)

### `class CIByteStream`

This is a small wrapper around raw byte read/write.

#### `virtual size_t stream_write(std::span<const uint8_t> data) const = 0;`

Writes raw bytes.

#### `virtual size_t stream_read(std::span<uint8_t> data) = 0;`

Reads raw bytes.

### `class CRTUTransport : public CTransport`

RTU transport built on top of `CIByteStream`.

#### `CRTUTransport(CIByteStream& byte_stream);`

Creates the RTU transport.

#### `ETransportError connect() override;`

Returns `None` in the current implementation.

#### `void close() override;`

Does nothing in the current implementation.

#### `ETransportError send(std::span<const uint8_t> data) override;`

Sends bytes through the byte stream.

#### `ETransportError receive(std::span<uint8_t> data, size_t& received) override;`

Reads bytes through the byte stream.

If nothing is read, it returns `Timeout`.

## Linux UART Byte Stream

File: [include/modbus/transport/uart_linux_bytestream.hpp](/home/mmagdi/workspace/modbus_lib/include/modbus/transport/uart_linux_bytestream.hpp)

### `class CUARTByteStream : public CIByteStream`

Linux UART byte stream using a device path like `/dev/ttyUSB0` or `/dev/pts/X`.

#### `CUARTByteStream(const std::string& device);`

Opens the device.

#### `size_t stream_write(std::span<const uint8_t> data) const override;`

Writes bytes to the device.

#### `size_t stream_read(std::span<uint8_t> data) override;`

Reads bytes from the device.

## PDU API

File: [include/modbus/core/modbus_pdu.hpp](/home/mmagdi/workspace/modbus_lib/include/modbus/core/modbus_pdu.hpp)

### `class CPDU`

Represents a Modbus Protocol Data Unit.

#### `CPDU(uint8_t function_code, std::vector<uint8_t> data);`

Creates a PDU from a function code and data bytes.

#### `uint8_t get_function_code() const;`

Returns the function code.

#### `std::span<const uint8_t> get_data() const;`

Returns the data bytes.

#### `bool is_exception() const;`

Returns `true` if the PDU is an exception response.

#### `uint8_t exception_code() const;`

Returns the Modbus exception code.

#### `CPDU exception(uint8_t fc, uint8_t code) const;`

Creates an exception PDU from a function code and exception code.

#### `size_t serialize(std::span<uint8_t> buffer) const;`

Writes the PDU into a byte buffer.

#### `static CPDU parse(std::span<uint8_t> bytes);`

Builds a PDU from raw bytes.

## Register Map API

File: [include/modbus/server/register_map.hpp](/home/mmagdi/workspace/modbus_lib/include/modbus/server/register_map.hpp)

### `class CRegisterMap`

Stores all Modbus data for the server.

#### `CRegisterMap(size_t coils_count, size_t discrete_input_count, size_t holding_register_count, size_t input_registers_count);`

Creates the register map with fixed sizes.

### Coil functions

#### `bool read_coil(uint16_t address) const;`

Reads one coil.

#### `void write_coil(uint16_t address, bool value);`

Writes one coil.

#### `size_t get_coil_count() const;`

Returns the number of coils.

### Discrete input functions

#### `bool read_discrete_input(uint16_t address) const;`

Reads one discrete input.

#### `size_t get_discrete_input_count() const;`

Returns the number of discrete inputs.

### Holding register functions

#### `uint16_t read_holding_register(uint16_t address) const;`

Reads one holding register.

#### `void write_holding_register(uint16_t address, uint16_t value);`

Writes one holding register.

#### `size_t get_holding_register_count() const;`

Returns the number of holding registers.

### Input register functions

#### `uint16_t read_input_register(uint16_t address) const;`

Reads one input register.

#### `size_t get_input_register_count() const;`

Returns the number of input registers.

## Server API

File: [include/modbus/server/modbus_server.hpp](/home/mmagdi/workspace/modbus_lib/include/modbus/server/modbus_server.hpp)

### `class CModbusServer`

Simple Modbus server.

#### `CModbusServer(CTransport& transport, CRegisterMap& registers);`

Creates the server.

#### `void poll();`

Reads one request, processes it, and sends one response.

Call this in a loop.

## Client API

File: [include/modbus/client/modbus_client.hpp](/home/mmagdi/workspace/modbus_lib/include/modbus/client/modbus_client.hpp)

### `class CModbusClient`

Simple Modbus client helper.

#### `CModbusClient(CTransport& transport);`

Creates the client.

#### `std::vector<uint16_t> read_holding_register(uint16_t start_address, uint16_t qunatity);`

Reads holding registers using function code `0x03`.

Returns the register values.

#### `void write_single_register(uint16_t address, uint16_t value);`

Writes one holding register using function code `0x06`.

## Server Function Codes

The server supports these function codes:

- `0x01` Read Coils
- `0x03` Read Holding Registers
- `0x04` Read Input Registers
- `0x05` Write Single Coil
- `0x06` Write Single Register
- `0x10` Write Multiple Registers

## Addressing

All addresses are zero-based inside the code.

Example:

- address `0` means the first item
- address `1` means the second item

## Examples

Example files:

- [examples/server_rtu_example.cpp](/home/mmagdi/workspace/modbus_lib/examples/server_rtu_example.cpp)
- [examples/client_rtu_example.cpp](/home/mmagdi/workspace/modbus_lib/examples/client_rtu_example.cpp)

These examples show:

- how to create transport
- how to create the register map
- how to start the server
- how to send client requests
- how to test the supported function codes
