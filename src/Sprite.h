#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <memory>

class Sprite {
    SDL_Texture *texture_;
    int width_;
    int height_;
    Sprite(SDL_Texture *texture_, int width, int height);

   public:
    int getWidth() const;
    int getHeight() const;
    SDL_Texture *getSDLTexture();
    static std::shared_ptr<Sprite> loadFromPng(std::string path,
                                               SDL_Renderer *renderer);
    ~Sprite();
};