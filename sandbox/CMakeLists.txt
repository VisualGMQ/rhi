include(../cmake/FindSDL.cmake)
include(../cmake/copydll.cmake)

add_executable(sandbox sandbox.cpp)
target_link_libraries(sandbox PRIVATE ${RHI_LIBRARY_NAME} SDL2)
target_include_directories(sandbox PRIVATE ../)
CopyDLL(sandbox)
