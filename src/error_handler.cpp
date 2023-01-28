#include "rhi/error_handler.hpp"

namespace rhi {

void ErrorHandler::Deal(std::string_view msg) {
    ThrowError(msg);
    // TODO use `Log` option
}

void ErrorHandler::ThrowError(std::string_view msg) {
    throw std::runtime_error(msg.data());
}

constexpr std::string_view LevelString[] = {
    "Warning",
    "Error",
};

void ErrorHandler::Log(Level level, std::string_view msg) {
    std::cerr << "[" << LevelString[static_cast<size_t>(level)] << "]: " << msg << std::endl;
}

ErrorHandler& ErrorHandler::Instance() {
    static ErrorHandler instance;
    return instance;
}

}