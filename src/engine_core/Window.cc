#include <SDL2/SDL_image.h>
#include "SdlFacade.h"
#include "Window.h"

Window::Window()
    : window_(sdl_facade::createSDLWindow("Heroes of Might & Magic 3",
                                          default_dimensions::WINDOW_WIDTH,
                                          default_dimensions::WINDOW_HEIGHT)) {}

Window::~Window() { SDL_DestroyWindow(window_); }

SDL_Renderer *Window::createSDLRenderer() {
    auto renderer = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    if (renderer == NULL) {
        sdl_facade::logSDLError("Could not initialize renderer");
    }
    return renderer;
}