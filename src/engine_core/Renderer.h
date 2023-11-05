#pragma once
#include <SDL2/SDL.h>
#include <memory>
#include "Sprite.h"
#include "Window.h"

class Renderer {
    std::unique_ptr<Window> window_;
    SDL_Renderer *renderer_;

   public:
    Renderer();
    ~Renderer();
    Renderer(Renderer const &rhs) = delete;
    Renderer &operator=(Renderer const &rhs) = delete;

    SDL_Renderer *getSDLRenderer();
    void clear();
    void swapBuffers();
    void renderSprite(std::unique_ptr<Sprite> const &sprite, int x, int y);
};

typedef std::unique_ptr<Renderer> RendererPtr;