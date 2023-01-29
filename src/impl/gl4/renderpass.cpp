#include "rhi/impl/gl4/renderpass.hpp"

namespace rhi::gl4 {

RenderPass::RenderPass(const std::vector<AttachmentReference>& references,
                       const std::vector<Subpass>& subpasses)
    : references_(references), subpasses_(subpasses) {}

}  // namespace rhi::gl4