#pragma once

#include "rhi/rhi.hpp"
#include "rhi/impl/gl4/shader.hpp"
#include "rhi/impl/gl4/buffer.hpp"
#include "rhi/impl/gl4/image.hpp"

namespace rhi::gl4 {

class Device : public rhi::Device {
public:
    Device();
    ~Device();

    std::shared_ptr<rhi::ShaderModule> CreateShaderModuleBySPIRV(
        const std::vector<uint32_t>& data, ShaderModule::Stage) override;
    std::shared_ptr<rhi::ShaderModule> CreateShaderModuleByCode(
        const std::string& code, ShaderModule::Stage) override;

    std::shared_ptr<rhi::Buffer> CreateBuffer(uint32_t size) override;

    std::shared_ptr<rhi::Image> CreateImage(
        void* data, uint32_t w, uint32_t h, rhi::Image::Type,
        rhi::Image::Format, rhi::Image::TargetFormat) override;
    std::shared_ptr<rhi::Sampler> CreateSampler(
        Sampler::Filter minFilter, Sampler::Filter maxFilter, Sampler::Wrap r,
        Sampler::Wrap s, Sampler::Wrap t) override;
    std::shared_ptr<rhi::ImageView> CreateImageView(const std::shared_ptr<rhi::Image>&) override;
    std::shared_ptr<RenderPass> CreateRenderPass(
        const std::vector<AttachmentReference>&, const std::vector<Subpass>&) override;
};

}