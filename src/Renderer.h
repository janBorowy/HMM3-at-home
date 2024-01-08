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
    Renderer(const Renderer &rhs) = delete;
    Renderer &operator=(const Renderer &rhs) = delete;

    SDL_Renderer *getSDLRenderer() const;
    Image createTextImage(std::string text, const ColorRGB &rgb) const;
    void clear();
    void setColor(Uint8 r, Uint8 g, Uint8 b);
    void swapBuffers();
    void drawEntity(const GameEntity &entity) const;
    void drawSprite(int x, int y, const Sprite &sprite) const;
    void drawSprite(int x, int y, const Sprite &sprite,
                    SDL_Rect &srcRect) const;
    void drawSprite(const Sprite &sprite, SDL_Rect &dstRect) const;
    void drawImage(int x, int y, const Image &image) const;
};

typedef std::shared_ptr<Renderer> RendererUPtr;