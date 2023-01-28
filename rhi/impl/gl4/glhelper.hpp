#pragma once

#include "glad/glad.h"
#include "rhi/error_handler.hpp"

namespace rhi::gl4 {

#define TRY_GET_GL_ERROR_MAX_LOOP 10000

const char* GLGetErrorString(GLenum);

void GLClearError();

#define GL_CALL(statement) do { \
    GLClearError(); \
    statement; \
    GLenum ___err_inner_use = glGetError(); \
    if (___err_inner_use != GL_NO_ERROR) { ErrorHandler::Instance().Log(ErrorHandler::Level::Error, GLGetErrorString(___err_inner_use)); } \
} while(0)

}