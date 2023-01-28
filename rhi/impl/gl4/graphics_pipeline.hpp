#pragma once

#include "rhi/rhi.hpp"

namespace rhi::gl4 {

class GraphicsPipeline : public GraphicsPipeline {
public:
    GraphicsPipeline(const GraphicsPipelineCreateInfo& info): info_(info) {
        // TODO  set pipeline state
    }

private:
    GraphicsPipelineCreateInfo info_;
};

}  // namespace rhi::gl4