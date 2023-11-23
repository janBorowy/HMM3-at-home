#include <iostream>
#include <string>
#include "GameWindow.h"

namespace {
void checkSDLerror() {
    std::string message = SDL_GetError();
    if (!message.empty()) {
        throw SDLException();
    }
}
}  // namespace

/*Static variable has to be initialized outside class*/
GameWindowUPtr GameWindow::instance_;

GameWindow::GameWindow()
    : window_(nullptr),
      renderer_(nullptr),
      windowWidth_(1600),
      windowHeight_(1000) {
    window_ = SDL_CreateWindow("Budget Heroes of Might & Magic 3",
                               SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                               windowWidth_, windowHeight_, SDL_WINDOW_SHOWN);
    checkSDLerror();
    if (!renderer_) {
        renderer_ = RendererUPtr(new Renderer(window_));
    }
    checkSDLerror();
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
    SDL_Quit();
}

void GameWindow::step() { SDL_GL_SwapWindow(window_); }
int GameWindow::width() { return windowWidth_; }
int GameWindow::height() { return windowHeight_; }