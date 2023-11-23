#pragma once
#include <SDL2/SDL.h>
#include <stdexcept>
#include "Renderer.h"

class SDLException : public std::runtime_error {
   public:
    SDLException() : runtime_error(SDL_GetError()) { SDL_ClearError(); }
};

class GameWindow {
    GameWindow();
    static std::unique_ptr<GameWindow> instance_;
    SDL_Window *window_;
    RendererUPtr renderer_;
    int windowWidth_;
    int windowHeight_;

   public:
    static GameWindow &getInstance();
    Renderer &getRenderer();
    void quit();
    int width();
    int height();
};

using GameWindowUPtr = std::unique_ptr<GameWindow>;