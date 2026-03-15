# modbus_lib

![C++](https://img.shields.io/badge/language-C++-blue.svg)
![Build](https://img.shields.io/badge/build-Makefile-green.svg)
![Protocol](https://img.shields.io/badge/protocol-Modbus%20RTU-orange.svg)
![Platform](https://img.shields.io/badge/platform-Linux-lightgrey.svg)

A lightweight **C++ Modbus RTU library** implementing both **client and server functionality** with a modular and extensible architecture.

The library is designed to be:

* Simple to understand
* Easy to extend with new function codes
* Portable by abstracting the transport layer

Core processing flow:

```
Transport → PDU → Dispatcher → Function Handler → Register Map
```

---

# Features

## Transport Support

* Modbus **RTU transport**
* Portable **byte stream abstraction**
* Linux **UART implementation**

## Server Implementation

The Modbus server supports the following function codes:

| Function | Description              |
| -------- | ------------------------ |
| `0x01`   | Read Coils               |
| `0x03`   | Read Holding Registers   |
| `0x04`   | Read Input Registers     |
| `0x05`   | Write Single Coil        |
| `0x06`   | Write Single Register    |
| `0x10`   | Write Multiple Registers |

The server is implemented using a **dispatcher + handler pattern**, making it easy to extend with additional function codes.

## Client API

The current client wrapper provides:

* Read holding registers
* Write single register

Additional function codes can be accessed by constructing raw PDUs.

---

# Architecture

The library is organized into several layers:

```
Application
     │
     ▼
Modbus Client / Server
     │
     ▼
Dispatcher + Function Handlers
     │
     ▼
Register Map
     │
     ▼
Transport Layer (RTU/TCP)
     │
     ▼
Byte Stream (UART / Socket / etc)
```

PlantUML diagrams are provided in the `docs/` directory:

* Class diagram
* Component diagram
* Sequence diagram

---

# Project Structure

```
modbus_lib
│
├── include/modbus/
│   Public library headers
│
│   ├── client/
│   ├── core/
│   ├── function_codes/
│   ├── server/
│   └── transport/
│
├── src/
│   Library implementation
│
│   ├── client/
│   ├── core/
│   ├── function_codes/
│   ├── server/
│   └── transport/
│
├── examples/
│   Example RTU client and server applications
│
├── build/
│   Generated build artifacts
│
├── docs/
│   Architecture diagrams and API docs
│
├── Makefile
└── README.md
```

---

# Quick Start

Clone the repository:

```bash
git clone https://github.com/<your-username>/modbus_lib.git
cd modbus_lib
```

Build the project:

```bash
make
```

This produces:

```
build/
├── libmodbus.a
└── examples/
    ├── client_rtu_example
    └── server_rtu_example
```

---

# Running the Examples (Linux Compatible)

The example programs demonstrate a **Modbus RTU client and server communicating over virtual UART devices**.

## 1. Create Virtual UART Devices

Install `socat` if needed:

```bash
sudo apt install socat
```

Create a pair of connected pseudo terminals:

```bash
socat -d -d pty,raw,echo=0 pty,raw,echo=0
```

Example output:

```
PTY is /dev/pts/6
PTY is /dev/pts/7
```

These behave like a serial cable:

```
/dev/pts/6  <-->  /dev/pts/7
```

---

## 2. Run the Server

```bash
./build/examples/server_rtu_example
```

The server:

* receives Modbus requests
* dispatches them to the correct handler
* accesses the register map
* sends a response

---

## 3. Run the Client

In another terminal:

```bash
./build/examples/client_rtu_example
```

The client performs operations such as:

* writing a register
* reading multiple registers

---

# Example Usage

## Server Application

```cpp
CUARTByteStream uart("/dev/ttyUSB0");
CRTUTransport transport(uart);

CRegisterMap registers(
    8,   // coils
    0,   // discrete inputs
    10,  // holding registers
    2    // input registers
);

CModbusServer server(transport, registers);

while (true) {
    server.poll();
}
```

---

## Client Application

```cpp
CUARTByteStream uart("/dev/ttyUSB0");
CRTUTransport transport(uart);

CModbusClient client(transport);

client.write_single_register(1, 999);

auto values = client.read_holding_register(0, 3);
```

---

# Modbus Data Model

The register map implements the four Modbus data areas:

| Type              | Size   | Access     |
| ----------------- | ------ | ---------- |
| Coils             | 1 bit  | Read/Write |
| Discrete Inputs   | 1 bit  | Read Only  |
| Holding Registers | 16 bit | Read/Write |
| Input Registers   | 16 bit | Read Only  |

Internally all addresses are **zero-based**.

---

# Testing

You can test the library using the provided examples.

Typical workflow:

```
1. Build project
2. Create virtual UART pair
3. Run server
4. Run client
5. Observe Modbus register transactions
```

The examples demonstrate:

* Modbus request generation
* register read/write operations
* full protocol round trip

---

# Demo Video (Running on Linux)
# Demo Video

Watch the demo here:

[▶ Run the Modbus library demo](https://drive.google.com/file/d/1N_yIPcRs9CotcM-G9l-sSoJm4FvgAD1W/view?usp=sharing)
---

# Error Handling

The server returns **Modbus exception responses** for invalid requests.

Supported exceptions:

| Code   | Meaning              |
| ------ | -------------------- |
| `0x01` | Illegal function     |
| `0x02` | Illegal data address |
| `0x03` | Illegal data value   |

---

# Extending the Library

The dispatcher + handler design allows new function codes to be added easily.

Steps to add a new Modbus function:

1. Create a new handler inheriting from `CFunctionHandler`
2. Implement the `handle()` method
3. Register the handler in `CFunctionDispatcher`

This allows the server to support additional protocol features without modifying existing logic.

---

# Future Improvements

Potential extensions include:

* Modbus TCP transport
* asynchronous server mode
* configurable register map generation
* improved client API coverage
* integration tests

---

# Documentation

Additional API documentation:

```
docs/api.md
```

Architecture diagrams are provided using **PlantUML**.

