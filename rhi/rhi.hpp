#pragma once

#include <memory>
#include <string>
#include <vector>

namespace rhi {

struct VertexInputLayout final {
    enum class Format {
        Int,
        Float,
        Double,
        Vec2,
        Vec3,
        Vec4,
        Mat22,
        Mat33,
        Mat44,
    };

    uint32_t location;
    uint32_t stride;
    uint32_t size;
    uint32_t offset;
    Format format;
};

struct VertexInputInfo final {
    std::vector<VertexInputLayout> layouts;
};

struct VertexAssemblyInfo final {
    enum class PrimitiveTopology {
        PointList = 0,
        TriangleList,
        TriangleStrip,
        TriangleFan,
        LineList,
        LineStrip,
    };

    PrimitiveTopology topology;
};

struct Rect2D final {
    float x, y, w, h;
};

struct ViewportInfo final {
    Rect2D viewport;
    Rect2D scissor;
};

struct FaceCullInfo final {
    enum class FrontFace {
        CW,
        CCW,
    };

    enum class CullMode {
        Front,
        Back,
    };

    CullMode cull;
    FrontFace front;
};

struct RasterizationInfo final {
    enum PolygonMode {
        None,
        Fill,
        Line,
    };

    FaceCullInfo faceCull;
    uint32_t lineWidth;
    PolygonMode polygon;
};

struct MultisampleInfo final {
    // TODO not finish
};

class ShaderModule {
public:
    enum class Stage {
        Vertex = 0,
        Fragment = 1,
    };

    ShaderModule(Stage stage) : stage_(stage) {}
    virtual ~ShaderModule() = default;

    virtual operator bool() const = 0;

protected:
    Stage stage_;
};

struct ShaderInfo {
    virtual operator bool() const = 0;

    virtual ~ShaderInfo() = default;
};

struct GraphicsPipelineCreateInfo final {
    VertexInputInfo vertexInput;
    VertexAssemblyInfo vertexAssembly;
    ViewportInfo viewport;
    RasterizationInfo rasterization;
    std::vector<ShaderInfo> shaders;
};

class GraphicsPipeline {
public:
    virtual ~GraphicsPipeline();
};

class Buffer {
public:
    virtual void BufferData(void* data, uint32_t offset, uint32_t size) = 0;

    virtual ~Buffer() = default;
};

class Image {
public:
    enum class Format {
        R8,
        R8_SNORM,
        R16,
        R16_SNORM,
        RG8,
        RG8_SNORM,
        RG16,
        RG16_SNORM,
        R3_G3_B2,
        RGB4,
        RGB5,
        RGB8,
        RGB8_SNORM,
        RGB10,
        RGB12,
        RGB16_SNORM,
        RGBA2,
        RGBA4,
        RGB5_A1,
        RGBA8,
        RGBA8_SNORM,
        RGB10_A2,
        RGB10_A2UI,
        RGBA12,
        RGBA16,
        SRGB8,
        SRGB8_ALPHA8,
        R16F,
        RG16F,
        RGB16F,
        RGBA16F,
        R32F,
        RG32F,
        RGB32F,
        RGBA32F,
        R11F_G11F_B10F,
        RGB9_E5,
        R8I,
        R8UI,
        R16I,
        R16UI,
        R32I,
        R32UI,
        RG8I,
        RG8UI,
        RG16I,
        RG16UI,
        RG32I,
        RG32UI,
        RGB8I,
        RGB8UI,
        RGB16I,
        RGB16UI,
        RGB32I,
        RGB32UI,
        RGBA8I,
        RGBA8UI,
        RGBA16I,
        RGBA16UI,
        RGBA32I,
        RGBA32UI,
    };

    enum class TargetFormat {
        Red = 0,
        RG,
        RGB,
        BGR,
        RGBA,
        BGRA,
        RedInt,
        RGInt,
        RGBInt,
        BGRInt,
        RGBAInt,
        BGRAInt,
        StencilIndex,
        DepthComponent,
        DepthStencil,
    };

    enum class Type {
        e2D = 0,
        e3D,
    };

    virtual ~Image() = default;
};

class Sampler {
public:
    enum class Filter {
        Nearest,
        Linear,
    };
    enum class Wrap {
        Clamp2Edge = 0,
        Clamp2Border,
        MirroredRepeat,
        Repeat,
        MirrorClamp2Edge
    };

    virtual ~Sampler() = default;
};

class ImageView {
public:
    virtual ~ImageView() = default;
};

class Framebuffer {
public:
    virtual ~Framebuffer() = default;
};

enum ImageLayout {
    Undefined = 0,
    Present,
    ColorAttachmentOptimal,
};

struct AttachmentDescription {
    enum class LoadOp {
        Clear = 0,
        DontCare,
    };

    enum class StoreOp {
        DontCare = 0,
        Store,
    };

    Image::Format format;
    LoadOp loadOp;
    StoreOp storeOp;
    ImageLayout initLayout;
    ImageLayout finalLayout;
};

struct AttachmentReference {
    uint32_t attachmentIndex;
    ImageLayout layout;
};

struct Subpass {
    std::vector<AttachmentReference> colorAttachments;
    std::vector<AttachmentReference> depthStencilAttachments;
};

class RenderPass {
public:
    virtual ~RenderPass() = default;
};

class CommandPool {
public:
    virtual ~CommandPool() = default;
};

class CommandBuffer {
public:
    virtual ~CommandBuffer() = default;

    virtual void Reset() = 0;
};

class Device {
public:
    virtual ~Device() = default;

    virtual std::shared_ptr<ShaderModule> CreateShaderModuleBySPIRV(
        const std::vector<uint32_t>& data, ShaderModule::Stage) = 0;
    virtual std::shared_ptr<rhi::ShaderModule> CreateShaderModuleByCode(
        const std::string& code, ShaderModule::Stage) = 0;

    virtual std::shared_ptr<Buffer> CreateBuffer(uint32_t size) = 0;

    virtual std::shared_ptr<Image> CreateImage(void* data, uint32_t w,
                                               uint32_t h, Image::Type,
                                               Image::Format,
                                               Image::TargetFormat) = 0;
    virtual std::shared_ptr<Sampler> CreateSampler(Sampler::Filter minFilter,
                                                   Sampler::Filter maxFilter,
                                                   Sampler::Wrap r,
                                                   Sampler::Wrap s,
                                                   Sampler::Wrap t) = 0;
    virtual std::shared_ptr<ImageView> CreateImageView(
        const std::shared_ptr<Image>&) = 0;
    virtual std::shared_ptr<RenderPass> CreateRenderPass(
        const std::vector<AttachmentReference>&, const std::vector<Subpass>&) = 0;
};

class Instance {
public:
    virtual ~Instance() = default;
    virtual Device* CreateDevice() = 0;
};

enum class RHIType {
#ifdef RHI_HAS_OPENGL
    GL4 = 0,
#endif
#ifdef RHI_HAS_VULKAN
    Vulkan = 1,
#endif
};

std::unique_ptr<Instance> CreateInstance(RHIType);

}  // namespace rhi