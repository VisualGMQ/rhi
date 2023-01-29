#include "rhi/impl/gl4/command.hpp"

namespace rhi::gl4 {

std::vector<rhi::CommandBuffer*> CommandPool::Allocate(uint32_t num) {
    std::vector<rhi::CommandBuffer*> cmdBufs;

    for (int i = 0; i < num; i++) {
        cmdBufs.push_back(AllocateOne());
    }

    return cmdBufs;
}

rhi::CommandBuffer* CommandPool::AllocateOne() {
    if (cache_.empty()) {
        instances_.push_back(std::make_unique<CommandBuffer>());
    } else {
        instances_.push_back(std::move(cache_.back()));
        cache_.pop_back();
        instances_.back()->Reset();
    }

    return instances_.back().get();
}

void CommandPool::Free(rhi::CommandBuffer& buf) {
    auto it = std::find_if(instances_.begin(), instances_.end(), [&](const std::unique_ptr<CommandBuffer>& cmdBuf) {
        return &buf == cmdBuf.get();
    });
}

void CommandPool::Reset() {
    for (auto& cmdBuf : instances_) {
        cmdBuf->Reset();
    }
}

}