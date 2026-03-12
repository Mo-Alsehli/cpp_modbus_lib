#pragma once

#include <span>

#include "transport.hpp"

// Wrapper for making system independant read/write.
class CIByteStream {
   public:
    virtual ~CIByteStream() = default;

    virtual size_t write(std::span<const uint8_t> data) const = 0;
    virtual size_t read(std::span<uint8_t> data) const = 0;
};

class CRTUTransport : public CTransport {
   public:
    CRTUTransport(CIByteStream& byte_stream);

    ETransportError send(std::span<const uint8_t> data) override;
    ETransportError receive(std::span<uint8_t> data, size_t& received) override;

   private:
    CIByteStream& m_byte_stream;
};