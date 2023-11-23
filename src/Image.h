#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <memory>

class Image {
    SDL_Texture *texture_;
    int width_;
    int height_;

   public:
    Image(SDL_Texture *texture_, int width, int height);
    int getWidth() const;
    int getHeight() const;
    SDL_Texture *getSDLTexture();
    ~Image();
};

using ImageUPtr = std::unique_ptr<Image>;