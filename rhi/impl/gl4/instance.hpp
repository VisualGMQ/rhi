#pragma once

#include "rhi/rhi.hpp"
#include "glad/glad.h"
#include "rhi/impl/gl4/device.hpp"

#include <memory>

namespace rhi::gl4 {

class Instance : public rhi::Instance {
public:
    Instance();
    ~Instance();

    rhi::Device* CreateDevice() override;

private:
    std::unique_ptr<Device> device_;
};

}