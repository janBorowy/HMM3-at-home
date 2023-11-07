#include <SDL2/SDL_image.h>
#include <algorithm>
#include <iostream>
#include <string>
#include "Engine.h"
#include "SdlFacade.h"
#include "components/SpriteComponent.h"

Engine::Engine() : renderer_(std::unique_ptr<Renderer>(new Renderer())) {
    registry_.putEntity(std::shared_ptr<GameEntity>(new GameEntity(
        new SpriteComponent("../images/selected_field.png", renderer_))));
}

void Engine::startLoop() {
    bool quit = false;
    SDL_Event e;
    while (!quit) {
        // input
        handleEvents(e, quit);
        // update game state
        renderer_->clear();
        // draw game entities
        for (auto &entity : registry_) {
            entity.second->render(renderer_);
        }
        renderer_->swapBuffers();
    }
}

void Engine::handleEvents(SDL_Event &e, bool &quit) {
    while (SDL_PollEvent(&e) != 0) {
        if (e.type == SDL_QUIT) {
            quit = true;
        }
        if (e.type == SDL_MOUSEBUTTONDOWN) {
            // check witch entity was clicked
            int x, y;
            SDL_GetMouseState(&x, &y);
            for (auto &pair : registry_) {
                auto entity = pair.second;
                SDL_Rect rect = entity->getPosition();
                if (x >= rect.x && x <= rect.x + rect.w && y >= rect.y &&
                    y <= rect.y + rect.h) {
                    entity->setState(IS_CLICKED);
                }
            }
        }
    }
}
