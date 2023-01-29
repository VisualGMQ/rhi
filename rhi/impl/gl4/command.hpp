#pragma once

#include "rhi/rhi.hpp"

namespace rhi::gl4 {

class CommandBuffer: public rhi::CommandBuffer {
public:
    void Reset() override;

private:
};

class CommandPool: public rhi::CommandPool {
public:
    std::vector<rhi::CommandBuffer*> Allocate(uint32_t num);
    rhi::CommandBuffer* AllocateOne();
    void Free(rhi::CommandBuffer&);
    void Reset();

private:
    std::vector<std::unique_ptr<CommandBuffer>> cache_;
    std::vector<std::unique_ptr<CommandBuffer>> instances_;

};

}