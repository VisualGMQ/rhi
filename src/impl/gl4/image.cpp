#include "rhi/impl/gl4/image.hpp"

namespace rhi::gl4 {

constexpr GLenum ImageTypeMapper[] = {
    GL_TEXTURE_2D,
    GL_TEXTURE_3D, 
};

constexpr GLenum ImageFormatMapper[] = {
    GL_R8,
    GL_R8_SNORM,
    GL_R16,
    GL_R16_SNORM,
    GL_RG8,
    GL_RG8_SNORM,
    GL_RG16,
    GL_RG16_SNORM,
    GL_R3_G3_B2,
    GL_RGB4,
    GL_RGB5,
    GL_RGB8,
    GL_RGB8_SNORM,
    GL_RGB10,
    GL_RGB12,
    GL_RGB16_SNORM,
    GL_RGBA2,
    GL_RGBA4,
    GL_RGB5_A1,
    GL_RGBA8,
    GL_RGBA8_SNORM,
    GL_RGB10_A2,
    GL_RGB10_A2UI,
    GL_RGBA12,
    GL_RGBA16,
    GL_SRGB8,
    GL_SRGB8_ALPHA8,
    GL_R16F,
    GL_RG16F,
    GL_RGB16F,
    GL_RGBA16F,
    GL_R32F,
    GL_RG32F,
    GL_RGB32F,
    GL_RGBA32F,
    GL_R11F_G11F_B10F,
    GL_RGB9_E5,
    GL_R8I,
    GL_R8UI,
    GL_R16I,
    GL_R16UI,
    GL_R32I,
    GL_R32UI,
    GL_RG8I,
    GL_RG8UI,
    GL_RG16I,
    GL_RG16UI,
    GL_RG32I,
    GL_RG32UI,
    GL_RGB8I,
    GL_RGB8UI,
    GL_RGB16I,
    GL_RGB16UI,
    GL_RGB32I,
    GL_RGB32UI,
    GL_RGBA8I,
    GL_RGBA8UI,
    GL_RGBA16I,
    GL_RGBA16UI,
    GL_RGBA32I,
    GL_RGBA32UI,
};

constexpr GLenum TargetFormatMapper[] = {GL_RED,           GL_RG,
                                         GL_RGB,           GL_BGR,
                                         GL_RGBA,          GL_BGRA,
                                         GL_RED_INTEGER,   GL_RG_INTEGER,
                                         GL_RGB_INTEGER,   GL_BGR_INTEGER,
                                         GL_RGBA_INTEGER,  GL_BGRA_INTEGER,
                                         GL_STENCIL_INDEX, GL_DEPTH_COMPONENT,
                                         GL_DEPTH_STENCIL};

Image::Image(void* data, uint32_t w, uint32_t h, Image::Format format, Image::TargetFormat targetFormat, Image::Type type) {
    glGenTextures(1, &image_);

    if (image_ == 0) {
        ErrorHandler::Instance().Log(ErrorHandler::Level::Error, "create image failed!");
    }

    glBindTexture(ImageTypeMapper[static_cast<size_t>(type)], image_);
    if (type == Image::Type::e2D) {
        glTexImage2D(ImageTypeMapper[static_cast<size_t>(type)], 0,
                     ImageFormatMapper[static_cast<size_t>(format)], w, h, 0,
                     TargetFormatMapper[static_cast<size_t>(targetFormat)],
                     GL_UNSIGNED_BYTE, data);
    } else if (type == Image::Type::e3D) {
        // TODO  set 3d image data
    }
}

Image::~Image() {
    glDeleteTextures(1, &image_);
}

constexpr GLenum FilterTypeMapper[] = {
    GL_NEAREST,
    GL_LINEAR,
};

constexpr GLenum WrapTypeMapper[] = {GL_CLAMP_TO_EDGE, GL_CLAMP_TO_BORDER,
                                     GL_MIRRORED_REPEAT, GL_REPEAT,
                                     GL_MIRROR_CLAMP_TO_EDGE};

Sampler::Sampler(rhi::Sampler::Filter minFilter, rhi::Sampler::Filter maxFilter,
                 rhi::Sampler::Wrap r, rhi::Sampler::Wrap s,
                 rhi::Sampler::Wrap t)
    : minFilter_(FilterTypeMapper[static_cast<size_t>(minFilter)]),
      maxFilter_(FilterTypeMapper[static_cast<size_t>(maxFilter)]),
      wrapR_(WrapTypeMapper[static_cast<size_t>(r)]),
      wrapS_(WrapTypeMapper[static_cast<size_t>(s)]),
      wrapT_(WrapTypeMapper[static_cast<size_t>(t)]) {}
}  // namespace rhi::gl4