#include "serial_transport.hpp"

#include "transport.hpp"

CRTUTransport::CRTUTransport(CIByteStream& byte_stream) : m_byte_stream(byte_stream) {}

ETransportError CRTUTransport::connect() { return ETransportError::None; }

void CRTUTransport::close() {}

ETransportError CRTUTransport::send(std::span<const uint8_t> data) {
    const size_t written = m_byte_stream.stream_write(data);

    if (written != data.size()) {
        return ETransportError::WriteError;
    }

    return ETransportError::None;
}

ETransportError CRTUTransport::receive(std::span<uint8_t> data, size_t& received) {
    received = m_byte_stream.stream_read(data);

    if (received == 0) {
        return ETransportError::Timeout;
    }

    return ETransportError::None;
}
