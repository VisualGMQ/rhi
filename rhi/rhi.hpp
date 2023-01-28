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

class Device {
public:
    virtual ~Device() = default;

    virtual std::shared_ptr<ShaderModule> CreateShaderModule(
        const std::vector<uint32_t>& data, ShaderModule::Stage) = 0;
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