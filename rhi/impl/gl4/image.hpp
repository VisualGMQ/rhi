#pragma once

#include "rhi/rhi.hpp"
#include "rhi/error_handler.hpp"
#include "glad/glad.h"

namespace rhi::gl4 {

class Image: public rhi::Image {
public:
    Image(void* data, uint32_t w, uint32_t h, Format, TargetFormat, Type);
    ~Image();

private:
    GLuint image_;
};

class Sampler: public rhi::Sampler {
public:
    Sampler(rhi::Sampler::Filter minFilter, rhi::Sampler::Filter maxFilter,
            rhi::Sampler::Wrap r, rhi::Sampler::Wrap s, rhi::Sampler::Wrap t);

private:
    GLenum minFilter_;
    GLenum maxFilter_;
    GLenum wrapR_;
    GLenum wrapS_;
    GLenum wrapT_;
};

class ImageView : public rhi::ImageView {
public:
    ImageView(const std::shared_ptr<Image>& image): image_(image) {}

private:
    std::shared_ptr<Image> image_;
};
}