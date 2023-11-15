#include <SDL2/SDL_image.h>
#include <algorithm>
#include <iostream>
#include <string>
#include "Engine.h"
#include "SdlFacade.h"
#include "components/BoxComponent.h"
#include "components/GridComponent.h"
#include "components/SpriteComponent.h"

Engine::Engine() : renderer_(std::unique_ptr<Renderer>(new Renderer())) {
    registry_.putEntity(std::shared_ptr<GameEntity>(new GameEntity(
        new GridComponent(70, 10, 12), new PositionComponent(0, 0))));
}

void Engine::startLoop() {
    bool quit = false;
    SDL_Event e;
    for (auto &entity : registry_) {
        if (entity.first == 2) {
            entity.second->setPosition(150, 100);
        } else if (entity.first == 3) {
            entity.second->setPosition(200, 200);
        }
    }
    while (!quit) {
        // input
        handleEvents(e, quit);
        // update game state
        renderer_->clear();
        drawGameEntities();
        renderer_->swapBuffers();
    }
}

void Engine::drawGameEntities() {
    for (auto &entity : registry_) {
        entity.second->render(renderer_);
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
