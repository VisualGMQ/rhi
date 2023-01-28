#pragma once

#include <exception>
#include <iostream>
#include <stdexcept>
#include <string_view>

namespace rhi {

class ErrorHandler final {
public:
    static ErrorHandler& Instance();

    enum class Level {
        Warning = 0,
        Error = 1,
    };

    void Deal(std::string_view);
    void ThrowError(std::string_view);
    void Log(Level, std::string_view);

private:
    ErrorHandler() = default;
};

}  // namespace rhi