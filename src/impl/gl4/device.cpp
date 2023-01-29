#include "rhi/impl/gl4/device.hpp"

namespace rhi::gl4 {

Device::Device() {}

Device::~Device() {}

std::shared_ptr<rhi::ShaderModule> Device::CreateShaderModuleBySPIRV(
    const std::vector<uint32_t>& data, ShaderModule::Stage stage) {
    auto module = std::make_shared<rhi::gl4::ShaderModule>(data, stage);
    return module;
}

std::shared_ptr<rhi::ShaderModule> Device::CreateShaderModuleByCode(
    const std::string& code, ShaderModule::Stage stage) {
    auto module = std::make_shared<rhi::gl4::ShaderModule>(code, stage);
    return module;
}

std::shared_ptr<rhi::Buffer> Device::CreateBuffer(uint32_t size) {
    return std::make_shared<rhi::gl4::Buffer>(size);
}

std::shared_ptr<rhi::Image> Device::CreateImage(
        void* data, uint32_t w, uint32_t h, rhi::Image::Type type,
        rhi::Image::Format format, rhi::Image::TargetFormat target) {
    return std::make_shared<rhi::gl4::Image>(data, w, h, format, target, type);
}

std::shared_ptr<rhi::Sampler> Device::CreateSampler(Sampler::Filter minFilter,
                                                    Sampler::Filter maxFilter,
                                                    Sampler::Wrap r,
                                                    Sampler::Wrap s,
                                                    Sampler::Wrap t) {
    return std::make_shared<rhi::gl4::Sampler>(minFilter, maxFilter, r, s, t);
}

std::shared_ptr<rhi::ImageView> Device::CreateImageView(const std::shared_ptr<rhi::Image>& image) {
    return std::make_shared<rhi::gl4::ImageView>(std::static_pointer_cast<rhi::gl4::Image>(image));
}

std::shared_ptr<RenderPass> Device::CreateRenderPass(
    const std::vector<AttachmentReference>& references,
    const std::vector<Subpass>& subpasses) {
    return std::make_shared<RenderPass>(references, subpasses);
}

}  // namespace rhi::gl4