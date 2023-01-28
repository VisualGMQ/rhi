#pragma once

#include "rhi/rhi.hpp"
#include "rhi/impl/gl4/shader.hpp"

namespace rhi::gl4 {

class Device : public rhi::Device {
public:
    Device();
    ~Device();

    virtual std::shared_ptr<rhi::ShaderModule> CreateShaderModule(
        const std::vector<uint32_t>& data, ShaderModule::Stage) override;
};

}