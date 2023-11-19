#include <iostream>
#include <string>
#include "GameWindow.h"
namespace {
SDL_Window *window = nullptr;
SDL_GLContext context = nullptr;
SDL_Renderer *renderer = nullptr;
int windowWidth = 1600;
int windowHeight = 1000;
bool checkSDLerror() {
    std::string message = SDL_GetError();
    if (!message.empty()) {
        std::cout << ("(SDL message: \"" + message + "\")") << std::endl;
        SDL_ClearError();
        return true;
    }

    return false;
}
}  // namespace

bool GameWindow::init() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        checkSDLerror();
        return false;
    }

    window = SDL_CreateWindow("Budget Heroes of Might & Magic 3",
                              SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                              windowWidth, windowHeight, SDL_WINDOW_SHOWN);
    if (checkSDLerror()) {
        return false;
    }
    return true;
}

std::shared_ptr<Renderer> GameWindow::getRenderer() {
    return std::shared_ptr<Renderer>(new Renderer(window));
}

void GameWindow::quit() {
    SDL_ShowCursor(true);
    if (window) SDL_DestroyWindow(window);
    SDL_Quit();
}

void GameWindow::step() { SDL_GL_SwapWindow(window); }
int GameWindow::width() { return windowWidth; }
int GameWindow::height() { return windowHeight; }