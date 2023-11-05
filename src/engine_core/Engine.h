#pragma once
#include <SDL2/SDL.h>
#include <memory>
#include <string>
#include <vector>
#include "GameEntity.h"
#include "Renderer.h"

class Engine {
    std::unique_ptr<Renderer> renderer_;
    std::vector<std::unique_ptr<GameEntity>> gameEntities;

   public:
    Engine();
    Engine(Engine const &rhs) = delete;
    Engine &operator=(Engine const &rhx) = delete;

    void startLoop();
};