#include "rhi/impl/gl4/buffer.hpp"

namespace rhi::gl4 {

Buffer::Buffer(uint32_t size) : size_(size) {
    glCreateBuffers(1, &buffer_);
    if (buffer_ == 0) {
        ErrorHandler::Instance().Log(ErrorHandler::Level::Error, "create buffer failed!");
    }
}

void Buffer::BufferData(void* data, uint32_t offset, uint32_t size) {
    glNamedBufferSubData(buffer_, offset, size, data);
}

Buffer::~Buffer() {
    glDeleteBuffers(1, &buffer_);
}

}