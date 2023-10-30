#pragma once
#include <SDL2/SDL.h>
#include <memory>
#include <string>
#include <vector>

#include "Renderer.h"
#include "GameEntity.h"

class Engine {
    
    std::unique_ptr<Renderer> renderer_;
    std::vector<std::unique_ptr<GameEntity>> gameEntities;

    public:
    Engine();
    Engine(const Engine &rhs) = delete;
    Engine &operator=(const Engine &rhx) = delete;
    
    void startLoop();
};