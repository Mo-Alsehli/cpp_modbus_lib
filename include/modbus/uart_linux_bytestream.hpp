#pragma once

#include <fcntl.h>
#include <unistd.h>

#include <cstdint>
#include <iostream>
#include <span>
#include <string>

#include "serial_transport.hpp"

class CUARTByteStream : CIByteStream {
   public:
    CUARTByteStream(const std::string& device);

    size_t stream_write(std::span<const uint8_t> data) const override;
    size_t stream_read(std::span<uint8_t> data) override;

   private:
    int m_fd;
};