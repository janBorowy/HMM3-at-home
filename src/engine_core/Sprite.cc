#include "Sprite.h"

Sprite::Sprite(SDL_Texture *texture, int width, int height)
    : texture_(texture), width_(width), height_(height) {}

Sprite::~Sprite() { SDL_DestroyTexture(texture_); }

std::shared_ptr<Sprite> Sprite::loadFromPng(std::string path,
                                            SDL_Renderer *renderer) {
    SDL_Surface *image_surface = IMG_Load(path.c_str());
    if (image_surface == NULL) {
        sdl_facade::logSDLError("Could not load surface from " + path);
    }
    auto texture = SDL_CreateTextureFromSurface(renderer, image_surface);
    if (texture == NULL) {
        sdl_facade::logSDLError("Could not create texture from " + path);
    }
    int width = image_surface->w;
    int height = image_surface->h;
    SDL_FreeSurface(image_surface);
    return std::shared_ptr<Sprite>(new Sprite(texture, width, height));
}

SDL_Texture *Sprite::getSDLTexture() { return texture_; }

int Sprite::getWidth() const { return width_; }

int Sprite::getHeight() const { return height_; }