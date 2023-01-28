cmake_minimum_required(VERSION 3.10)
project(RHI
        LANGUAGES C CXX
        DESCRIPTION "A Render Hardware Implementation insprited by wgpu")

include(cmake/FindOpenGL.cmake)
include(cmake/FindVulkan.cmake)

aux_source_directory(src SRC)

set(RHI_LIBRARY_NAME rhi)

if (${OpenGL_OpenGL_FOUND})
    list(APPEND SRC ${SRC} "${CMAKE_CURRENT_SOURCE_DIR}/src/impl/gl4/glad/src/glad.c")
    aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src/impl/gl4 SRC)
endif()

add_library(${RHI_LIBRARY_NAME} STATIC ${SRC})
target_compile_features(${RHI_LIBRARY_NAME} PUBLIC cxx_std_17)
target_include_directories(${RHI_LIBRARY_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

if (${Vulkan_FOUND})
    target_link_libraries(${RHI_LIBRARY_NAME} PRIVATE Vulkan::Vulkan)
    target_compile_definitions(${RHI_LIBRARY_NAME} PUBLIC RHI_HAS_VULKAN)
    message("support vulkan")
endif()

if (${OpenGL_OpenGL_FOUND})
    target_link_libraries(${RHI_LIBRARY_NAME} PRIVATE OpenGL::GL)
    target_compile_definitions(${RHI_LIBRARY_NAME} PUBLIC RHI_HAS_OPENGL)
    target_include_directories(${RHI_LIBRARY_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/rhi/impl/gl4/glad/include")
    message("support opengl")
endif()

add_subdirectory(sandbox)