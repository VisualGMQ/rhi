#pragma once

#include "rhi/rhi.hpp"
#include "glad/glad.h"
#include "rhi/error_handler.hpp"

namespace rhi::gl4 {

class Buffer : public rhi::Buffer {
public:
    Buffer(uint32_t size);
    void BufferData(void* data, uint32_t offset, uint32_t size) override;
    ~Buffer();

private:
    uint32_t size_;
    GLuint buffer_;
};

}