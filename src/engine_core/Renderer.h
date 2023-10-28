#pragma once
#include <SDL2/SDL.h>
#include <memory>
#include "Window.h"
#include "Sprite.h"

class Renderer {
    std::unique_ptr<Window> window_;
    SDL_Renderer *renderer_;

    public:
    Renderer();
    ~Renderer();
    Renderer(const Renderer &rhs) = delete;
    Renderer &operator=(const Renderer &rhs) = delete;

    SDL_Renderer *getSDLRenderer();
    void clear();
    void swapBuffers();
    void renderSprite(const std::unique_ptr<Sprite> &sprite, int x, int y);
};