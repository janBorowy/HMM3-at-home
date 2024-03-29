#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdexcept>
#include "Renderer.h"

constexpr int GAME_WINDOW_WIDTH = 1600;
constexpr int GAME_WINDOW_HEIGHT = 1000;

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
    SDL_Window *getSDLWindow() const;
    void quit();
    int width();
    int height();
};

using GameWindowUPtr = std::unique_ptr<GameWindow>;