#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <chrono>
#include <iostream>
#include <thread>
#include "GameData.h"
#include "GameWindow.h"
#include "MainPanel.h"
#include "MapParser.h"
#include "UI.h"
#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_sdlrenderer2.h"

constexpr int FRAMES_PER_SECOND = 60;

int gameLoop();

int main() {
    GameWindow &gameWindow = GameWindow::getInstance();
    // Render once to show something other, rather than black window
    GameData::setRenderer(gameWindow.getRenderer().getSDLRenderer());
    GameData::load();

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();

    int gameLoopReturnCode = gameLoop();
    gameWindow.quit();
    ImGui_ImplSDLRenderer2_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
    return gameLoopReturnCode;
}

int gameLoop() {
    UI panels;
    GameWindow &gameWindow = GameWindow::getInstance();
    Renderer &renderer = gameWindow.getRenderer();

#ifdef SDL_HINT_IME_SHOW_UI
    SDL_SetHint(SDL_HINT_IME_SHOW_UI, "1");
#endif

    renderer.swapBuffers();
    ImGui_ImplSDL2_InitForSDLRenderer(gameWindow.getSDLWindow(),
                                      renderer.getSDLRenderer());
    ImGui_ImplSDLRenderer2_Init(renderer.getSDLRenderer());
    try {
        panels.push(new MainPanel(renderer));
    } catch (MapParserException const &e) {
        std::cout << "Error parsing map file" << std::endl;
        return 1;
    }
    while (!panels.isDone()) {
        SDL_Event event;
        SDL_PollEvent(&event);
        ImGui_ImplSDL2_ProcessEvent(&event);
        if (event.type == SDL_QUIT) {
            panels.quit();
        } else if (panels.handle(event)) {
            // UI handled the event
        }
        renderer.clear();
        panels.drawFront(renderer);
        renderer.swapBuffers();
    }
    return 0;
}