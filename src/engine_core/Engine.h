#pragma once
#include <SDL2/SDL.h>
#include <memory>
#include <string>
#include <vector>
#include "EntityRegistry.h"
#include "GameEntity.h"
#include "Renderer.h"

class Engine {
    std::shared_ptr<Renderer> renderer_;
    EntityRegistry registry_;

    // class Prototypes {
    //    public:
    //     GameEntity selectedFieldPrototype = GameEntity(
    //         new SpriteComponent("../images/selected_field.png", renderer_));
    // };

   public:
    Engine();
    Engine(Engine const &rhs) = delete;
    Engine &operator=(Engine const &rhx) = delete;

    void startLoop();
    void handleEvents(SDL_Event &e, bool &quit);
};