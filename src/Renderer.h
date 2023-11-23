#pragma once
#include <SDL2/SDL.h>
#include <memory>
#include "GameEntity.h"

class Renderer {
    SDL_Renderer *renderer_;
    SDL_Window *window_;

   public:
    Renderer(SDL_Window *window);
    ~Renderer();
    Renderer(Renderer const &rhs) = delete;
    Renderer &operator=(Renderer const &rhs) = delete;

    SDL_Renderer *getSDLRenderer();
    void clear();
    void setColor(Uint8 r, Uint8 g, Uint8 b);
    void swapBuffers();
    void drawEntity(GameEntity const &entity);
    void drawLine(int startX, int startY, int endX, int endY);
};

typedef std::shared_ptr<Renderer> RendererUPtr;