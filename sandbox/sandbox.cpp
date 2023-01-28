#include "SDL.h"
#include "rhi/rhi.hpp"

int main(int argc, char** argv) {
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* window = SDL_CreateWindow("sandbox", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED_MASK, 1024, 720, SDL_WINDOW_SHOWN);

    bool shouldClose = false;
    SDL_Event event;

    std::unique_ptr<rhi::Instance> instance = rhi::CreateInstance(rhi::RHIType::GL4);
    rhi::Device* device = instance->CreateDevice(); 

    while (!shouldClose) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                shouldClose = true;
            }
        }
    }

    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}