#include "Engine.h"
#include "SdlFacade.h"
#include "components/SpriteComponent.h"
#include <SDL2/SDL_image.h>
#include <algorithm>
#include <iostream>
#include <string>

Engine::Engine() : renderer_(std::unique_ptr<Renderer>(new Renderer())) {
  gameEntities.push_back(std::unique_ptr<GameEntity>(
      new GameEntity(new SpriteComponent("../images/Archer.png", renderer_))));
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
    for (auto &entity : gameEntities) {
      entity->render(renderer_);
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
      for (auto &entity : gameEntities) {
        SDL_Rect rect = entity->getPosition();
        if (x >= rect.x && x <= rect.x + rect.w && y >= rect.y &&
            y <= rect.y + rect.h) {
          entity->setState(IS_CLICKED);
        }
      }
    }
  }
}
