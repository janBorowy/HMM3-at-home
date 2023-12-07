#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <memory>
#include <string>
#include <tuple>
#include "GameEntity.h"

using ColorRGB = std::tuple<u_int8_t, u_int8_t, u_int8_t>;

class Renderer {
    SDL_Renderer *renderer_;
    SDL_Window *window_;
    TTF_Font *font_;

   public:
    Renderer(SDL_Window *window);
    ~Renderer();
    Renderer(Renderer const &rhs) = delete;
    Renderer &operator=(Renderer const &rhs) = delete;

    SDL_Renderer *getSDLRenderer() const;
    Image createTextImage(std::string text, ColorRGB const &rgb) const;
    void clear();
    void setColor(Uint8 r, Uint8 g, Uint8 b);
    void swapBuffers();
    void drawEntity(GameEntity const &entity) const;
    void drawSprite(int x, int y, Sprite const &sprite) const;
    void drawImage(int x, int y, Image const &image) const;
};

typedef std::shared_ptr<Renderer> RendererUPtr;