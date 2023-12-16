#pragma once
#include <SDL2/SDL.h>
#include <string>
#include <tuple>
#include "Renderer.h"

class Label {
   protected:
    std::string text_;
    ImageUPtr image_;
    const Renderer &renderer_;
    ColorRGB color_;
    unsigned short x_;
    unsigned short y_;

   public:
    Label(std::string initalText, const Renderer &renderer);
    void updateText(std::string Text);
    void draw() const;
    void setPos(int x, int y);
};