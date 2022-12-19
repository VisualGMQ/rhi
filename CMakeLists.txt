cmake_minimum_required(VERSION 3.10)
project(RHI
        LANGUAGES C CXX
        DESCRIPTION "A Render Hardware Implementation insprited by wgpu")

include(cmake/FindOpenGL.cmake)
include(cmake/FindVulkan.cmake)

aux_source_directory(src SRC)
add_library(rhi STATIC ${SRC})
target_compile_features(rhi PUBLIC cxx_std_17)

if (${Vulkan_FOUND})
    target_link_libraries(rhi PRIVATE Vulkan::Vulkan)
    target_compile_definitions(rhi PRIVATE RHI_HAS_VULKAN)
endif()

if (${OPENGL_FOUND})
    target_link_libraries(rhi PRIVATE OpenGL::GL)
    target_compile_definitions(rhi PRIVATE RHI_HAS_OPENGL)
endif()

add_subdirectory(sandbox)