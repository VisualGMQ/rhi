#pragma once

#include "rhi/rhi.hpp"

namespace rhi::gl4 {

class RenderPass : public rhi::RenderPass {
public:
    RenderPass(const std::vector<AttachmentReference>& references,
               const std::vector<Subpass>& subpasses);

private:
    std::vector<AttachmentReference> references_;
    std::vector<Subpass> subpasses_;
};

}  // namespace rhi::gl4