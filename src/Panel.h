#pragma once
#include <SDL2/SDL.h>
#include <memory>
#include "Renderer.h"
struct UI;
struct Panel {
    Panel() = default;
    void setUI(UI *ui);
    virtual void step() = 0;
    virtual void draw(Renderer const &renderer) = 0;
    virtual bool keyDown(SDL_Keycode key, Uint16 mod, bool isNewPress) = 0;
    virtual bool mouseButtonDown(int x, int y) = 0;

   protected:
    UI *ui_;
};