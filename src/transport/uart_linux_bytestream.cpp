#include "uart_linux_bytestream.hpp"

CUARTByteStream::CUARTByteStream(const std::string& device) {
    m_fd = open(device.c_str(), O_RDWR | O_NOCTTY);

    if (m_fd < 0) {
        std::cerr << "Faild to open UART Device" << std::endl;
    }
}

size_t CUARTByteStream::stream_write(std::span<const uint8_t> data) const { return write(m_fd, data.data(), data.size()); }
size_t CUARTByteStream::stream_read(std::span<uint8_t> data) { return read(m_fd, data.data(), data.size()); }