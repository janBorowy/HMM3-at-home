#include <iostream>
#include <string>
#include "Image.h"

Image::Image(SDL_Texture *texture, int width, int height)
    : texture_(texture), width_(width), height_(height) {}

Image::~Image() { SDL_DestroyTexture(texture_); }

SDL_Texture *Image::getSDLTexture() { return texture_; }

int Image::getWidth() const { return width_; }

int Image::getHeight() const { return height_; }