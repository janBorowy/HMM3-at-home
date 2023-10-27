#include <string>

#include <SDL2/SDL.h>

namespace sdl_facade{
    void logSDLError(std::string message);
    SDL_Window *createSDLWindow(const char *title, unsigned int width, unsigned height);
    SDL_Renderer *createSDLRenderer(SDL_Window *window);
    void initializeSDLImage();
}