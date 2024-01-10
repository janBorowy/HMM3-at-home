#include "GameWindow.h"
#include <iostream>
#include <string>
#include "SDLUtils.h"

/*Static variable has to be initialized outside class*/
GameWindowUPtr GameWindow::instance_;

GameWindow::GameWindow()
    : window_(nullptr),
      renderer_(nullptr),
      windowWidth_(GAME_WINDOW_WIDTH),
      windowHeight_(GAME_WINDOW_HEIGHT) {
    SDL_Init(SDL_INIT_VIDEO);
    SDLError::checkSDLError();
    IMG_Init(IMG_INIT_PNG);
    TTF_Init();
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
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

int GameWindow::width() { return windowWidth_; }
int GameWindow::height() { return windowHeight_; }

SDL_Window *GameWindow::getSDLWindow() const { return window_; }