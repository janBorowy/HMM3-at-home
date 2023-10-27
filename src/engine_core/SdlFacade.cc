#include <iostream>
#include <SDL2/SDL_image.h>

#include "SdlFacade.h"

void sdl_facade::logSDLError(std::string message) {
    std::cout << message << ": " << SDL_GetError() << std::endl;
}

SDL_Window *sdl_facade::createSDLWindow(const char *title, unsigned int width, unsigned height) {
    auto window = SDL_CreateWindow("Heroes of Might & Magic 3",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        width,
        height,
        SDL_WINDOW_SHOWN);

        if(window == NULL) {
            logSDLError("Could not initialize window");
        }
        return window;
}

SDL_Renderer *sdl_facade::createSDLRenderer(SDL_Window *window) {
    auto renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

    if(renderer == NULL) {
        sdl_facade::logSDLError("Could not initialize renderer");
    }
    return renderer;
}

void sdl_facade::initializeSDLImage() {
    int flags = IMG_INIT_PNG;
    if(!(IMG_Init(flags)) & flags) {
        sdl_facade::logSDLError("Could not initialize image library");
    }
}