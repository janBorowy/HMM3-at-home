#pragma once
#include <SDL2/SDL.h>
#include <string>
#include <tuple>
#include "Renderer.h"

class Label {
    std::string text_;
    ImageUPtr image_;
    Renderer const &renderer_;
    ColorRGB color_;
    unsigned short x_;
    unsigned short y_;

   public:
    Label(std::string initalText, Renderer const &renderer);
    void updateText(std::string Text);
    void draw() const;
    void setPos(int x, int y);
};