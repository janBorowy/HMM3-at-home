#pragma once
#include <SDL2/SDL.h>
#include <stdexcept>
#include "SDL2/SDL_ttf.h"

class SDLException : public std::runtime_error {
   public:
    SDLException() : runtime_error(SDL_GetError()) { SDL_ClearError(); }
};

class TTFException : public std::runtime_error {
   public:
    TTFException() : runtime_error(TTF_GetError()) {}
};

class SDLError {
   public:
    SDLError() = delete;
    static void checkSDLError();
    static void checkTTFError();
};