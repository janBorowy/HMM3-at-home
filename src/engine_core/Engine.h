#pragma once
#include <SDL2/SDL.h>
#include <memory>
#include <string>
#include <array>

#include "Renderer.h"
#include "GameEntity.h"

constexpr int MAX_ENTITY_COUNT = 512;

class Engine {
    
    std::unique_ptr<Renderer> renderer_;
    std::array<std::shared_ptr<GameEntity>, MAX_ENTITY_COUNT> gameEntities;
    int entityCounter_;

    public:
    Engine();
    Engine(const Engine &rhs) = delete;
    Engine &operator=(const Engine &rhx) = delete;
    
    void startLoop();
};