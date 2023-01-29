#include "rhi/impl/gl4/shader.hpp"

namespace rhi::gl4 {

static uint32_t ShaderStageMap[] = {
    GL_VERTEX_SHADER,
    GL_FRAGMENT_SHADER,
};

ShaderModule::ShaderModule(const std::string& code,
                           rhi::ShaderModule::Stage stage)
    : rhi::ShaderModule(stage) {
    shader_ = glCreateShader(ShaderStageMap[static_cast<size_t>(stage)]);
    if (shader_ == 0) {
        ErrorHandler::Instance().Deal("OpenGL ShaderModule create failed");
    }

    const char* data = code.data();
    const GLchar** codes = &data;
    GL_CALL(glShaderSource(shader_, 1, codes, nullptr));
    glCompileShader(shader_);
    GLint state;
    GL_CALL(glGetShaderiv(shader_, GL_COMPILE_STATUS, &state));
    if (state != GL_NO_ERROR) {
        char buf[1024] = {0};
        glGetShaderInfoLog(shader_, sizeof(buf), nullptr, buf);
        ErrorHandler::Instance().Log(ErrorHandler::Level::Error, buf);
        glDeleteShader(shader_);
        shader_ = 0;
    }
}

ShaderModule::ShaderModule(const std::vector<uint32_t>& spir_v,
                           rhi::ShaderModule::Stage stage)
    : rhi::ShaderModule(stage) {
    // TODO use SPIR-V
    assert(false);
}

ShaderModule::~ShaderModule() {
    glDeleteShader(shader_);
}

ShaderInfo::ShaderInfo(ShaderModule& vertex, ShaderModule& fragment) {
    program_ = glCreateProgram();
    if (program_ == 0) {
        ErrorHandler::Instance().Log(ErrorHandler::Level::Error,
                                     "OpenGL shader create failed");
    } else {
        GL_CALL(glAttachShader(program_, vertex.GetShader()));
        GL_CALL(glAttachShader(program_, fragment.GetShader()));
        glLinkProgram(program_);
        GLint state;
        glGetProgramiv(program_, GL_LINK_STATUS, &state);
        if (state != GL_NO_ERROR) {
            char buf[1024] = {0};
            glGetProgramInfoLog(program_, sizeof(buf), nullptr, buf);
            ErrorHandler::Instance().Log(ErrorHandler::Level::Error, buf);
            glDeleteProgram(program_);
            program_ = 0;
        }
    }
}

ShaderInfo::~ShaderInfo() {
    glDeleteProgram(program_);
}

}  // namespace rhi::gl4