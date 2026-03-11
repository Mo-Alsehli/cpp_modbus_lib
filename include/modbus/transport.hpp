#pragma once

#include <cstdint>
#include <span>

enum class ETransportError { None, Timeout, Disconnected, IOError };

class CTransport {
   public:
    virtual ~CTransport() = default;

    virtual ETransportError connect() = 0;
    virtual void close() = 0;

    virtual ETransportError send(std::span<uint8_t> data) = 0;

    virtual ETransportError receive(std::span<uint8_t> data, size_t& received) = 0;
};