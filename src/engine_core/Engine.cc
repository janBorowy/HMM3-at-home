#include <SDL2/SDL_image.h>
#include <algorithm>
#include <iostream>
#include <string>
#include "Engine.h"
#include "SdlFacade.h"
#include "components/SpriteComponent.h"

Engine::Engine() : renderer_(std::unique_ptr<Renderer>(new Renderer())) {
    gameEntities.push_back(
        std::unique_ptr<GameEntity>(new GameEntity(new SpriteComponent(
            "/home/janek/workspace/Heroes-3-clone/.secret/zadanie.png",
            renderer_))));
}

void Engine::startLoop() {
    bool quit = false;
    SDL_Event e;
    while (!quit) {
        // input
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }
        // update game state
        renderer_->clear();
        // draw game entities
        for (auto &entity : gameEntities) {
            entity->render(renderer_);
        }
        renderer_->swapBuffers();
    }
}
