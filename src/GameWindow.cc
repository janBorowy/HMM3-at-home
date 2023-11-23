#include <iostream>
#include <string>
#include "GameWindow.h"
#include "SDLUtils.h"

/*Static variable has to be initialized outside class*/
GameWindowUPtr GameWindow::instance_;

GameWindow::GameWindow()
    : window_(nullptr),
      renderer_(nullptr),
      windowWidth_(1600),
      windowHeight_(1000) {
    SDL_Init(SDL_INIT_VIDEO);
    SDLError::checkSDLError();
    IMG_Init(IMG_INIT_PNG);
    window_ = SDL_CreateWindow("Budget Heroes of Might & Magic 3",
                               SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                               windowWidth_, windowHeight_, SDL_WINDOW_SHOWN);
    SDLError::checkSDLError();
    if (!renderer_) {
        renderer_ = RendererUPtr(new Renderer(window_));
    }
    SDLError::checkSDLError();
}

GameWindow &GameWindow::getInstance() {
    if (!instance_) {
        instance_ = GameWindowUPtr(new GameWindow());
    }
    return *instance_;
}

Renderer &GameWindow::getRenderer() { return *renderer_; }

void GameWindow::quit() {
    SDL_ShowCursor(true);
    if (window_) SDL_DestroyWindow(window_);
    IMG_Quit();
    SDL_Quit();
}

int GameWindow::width() { return windowWidth_; }
int GameWindow::height() { return windowHeight_; }