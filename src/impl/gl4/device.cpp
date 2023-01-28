#include "rhi/impl/gl4/device.hpp"

namespace rhi::gl4 {

Device::Device() {}

Device::~Device() {}

std::shared_ptr<rhi::ShaderModule> Device::CreateShaderModule(
    const std::vector<uint32_t>& data, ShaderModule::Stage stage) {
    auto module = std::shared_ptr<rhi::gl4::ShaderModule>(data, stage);
    return module;
}

}  // namespace rhi::gl4