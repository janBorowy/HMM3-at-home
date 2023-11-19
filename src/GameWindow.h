#pragma once
#include <SDL2/SDL.h>
#include "Renderer.h"

class GameWindow {
   public:
    static bool init();
    static void quit();
    static void step();
    static int width();
    static int height();
    static std::shared_ptr<Renderer> getRenderer();
};