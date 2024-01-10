#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <chrono>
#include <iostream>
#include <thread>
#include "Battle.h"
#include "BattlePanel.h"
#include "GameData.h"
#include "GameWindow.h"
#include "HeroResources.h"
#include "MainPanel.h"
#include "MapParser.h"
#include "StartPanel.h"
#include "UI.h"
#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_sdlrenderer2.h"

constexpr int MAX_FRAME_RATE = 60;

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
        panels.push(new StartPanel(renderer));
    } catch (const MapParserException &e) {
        std::cout << "Error parsing map file" << std::endl;
        return 1;
    }
    while (!panels.isDone()) {
        int64_t frameStart = SDL_GetPerformanceCounter();

        SDL_Event event;
        while (SDL_PollEvent(&event) != 0) {
            ImGui_ImplSDL2_ProcessEvent(&event);
            if (event.type == SDL_QUIT) {
                panels.quit();
            } else if (panels.handle(event)) {
                // UI handled the event
            }
        }
        renderer.clear();
        panels.drawFront(renderer);
        renderer.swapBuffers();

        int64_t frameEnd = SDL_GetPerformanceCounter();
        float frameDurationInMilliseconds =
            (frameEnd - frameStart) / (float)SDL_GetPerformanceFrequency() *
            1000.0f;
        auto cappedFrameDuration = (1000.0f / MAX_FRAME_RATE);
        if (cappedFrameDuration - frameDurationInMilliseconds > 0.0f) {
            SDL_Delay(cappedFrameDuration - frameDurationInMilliseconds);
        }
    }
    return 0;
}