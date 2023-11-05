#pragma once
#include <SDL2/SDL.h>
#include <string>

namespace sdl_facade {
void logSDLError(std::string message);
SDL_Window *createSDLWindow(char const *title, unsigned int width,
                            unsigned height);
SDL_Renderer *createSDLRenderer(SDL_Window *window);
void initializeSDLImage();
}  // namespace sdl_facade