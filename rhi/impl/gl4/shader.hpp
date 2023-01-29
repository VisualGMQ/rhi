#pragma once

#include "glad/glad.h"
#include "rhi/error_handler.hpp"
#include "rhi/rhi.hpp"
#include "rhi/impl/gl4/glhelper.hpp"

#include <cassert>

namespace rhi::gl4 {

class ShaderModule : public rhi::ShaderModule {
public:
    ShaderModule(const std::string& code, rhi::ShaderModule::Stage);
    ShaderModule(const std::vector<uint32_t>& spir_v, rhi::ShaderModule::Stage);
    ~ShaderModule();

    operator bool() const {
        return shader_ != 0;
    }

    GLuint GetShader() const { return shader_; }

private:
    GLuint shader_ = 0;
};

class ShaderInfo : public rhi::ShaderInfo {
public:
    ShaderInfo(ShaderModule& vertex, ShaderModule& fragment);
    ~ShaderInfo();

    operator bool() const {
        return program_ != 0;
    }

private:
    GLuint program_ = 0;
};

}  // namespace rhi::gl4