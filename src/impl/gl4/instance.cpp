#include "rhi/impl/gl4/instance.hpp"

namespace rhi::gl4 {

Instance::Instance() {
    gladLoadGL();
}

Instance::~Instance() {
}

rhi::Device* Instance::CreateDevice() {
    device_.reset(new Device());
    return device_.get();
}

}  // namespace rhi::gl4