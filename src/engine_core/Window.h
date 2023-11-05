#pragma once
#include <SDL2/SDL.h>

namespace default_dimensions {
constexpr int WINDOW_WIDTH = 1600;
constexpr int WINDOW_HEIGHT = 900;
}  // namespace default_dimensions

class Window {
    SDL_Window *window_;

   public:
    Window();
    ~Window();
    SDL_Renderer *createSDLRenderer();
};