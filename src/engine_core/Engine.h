#pragma once
#include <SDL2/SDL.h>
#include <memory>
#include <string>
#include <vector>
#include "EntityRegistry.h"
#include "GameEntity.h"
#include "Renderer.h"

class Engine {
    std::unique_ptr<Renderer> renderer_;
    EntityRegistry registry;

   public:
    Engine();
    Engine(Engine const &rhs) = delete;
    Engine &operator=(Engine const &rhx) = delete;

    void startLoop();
    void handleEvents(SDL_Event &e, bool &quit);
};