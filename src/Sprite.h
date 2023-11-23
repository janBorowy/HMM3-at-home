#pragma once
#include "Image.h"

struct Sprite {
    unsigned short width_;
    unsigned short height_;
    ImagePtr image_;
    Sprite(unsigned short width, unsigned short height, ImagePtr image);
};

using SpriteUPtr = std::unique_ptr<Sprite>;