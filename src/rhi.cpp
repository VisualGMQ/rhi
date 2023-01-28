#include "rhi/rhi.hpp"

#ifdef RHI_HAS_OPENGL
#include "rhi/impl/gl4/instance.hpp"
#endif

#ifdef RHI_HAS_VULKAN
// TODO include vulkan instance
#endif

#if !(defined(RHI_HAS_OPENGL) || defined(RHI_HAS_VULKAN))
#error "no supported graphics api, your GPU must support vulkan or opengl"
#endif

namespace rhi {

std::unique_ptr<Instance> CreateInstance(RHIType type) {
    uint32_t rhi_type = static_cast<uint32_t>(type);
    if (rhi_type == 0) {
#ifdef RHI_HAS_OPENGL
        return std::make_unique<gl4::Instance>();
#endif
    } else if (rhi_type == 1) {
#ifdef RHI_HAS_VULKAN
        return std::make_unique<vulkan::Instance>();
#endif
    }
    return nullptr;
}

}  // namespace rhi