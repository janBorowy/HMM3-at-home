#pragma once

#include <SDL2/SDL.h>
#include <stdexcept>

class SDLException : public std::runtime_error {
   public:
    SDLException() : runtime_error(SDL_GetError()) { SDL_ClearError(); }
};

class SDLError {
   public:
    SDLError() = delete;
    static void checkSDLError();
};