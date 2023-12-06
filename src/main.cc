#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <chrono>
#include <iostream>
#include <thread>
#include "GameData.h"
#include "GameWindow.h"
#include "MainPanel.h"
#include "UI.h"
#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_sdlrenderer2.h"

constexpr int FRAMES_PER_SECOND = 60;

void gameLoop();

using SteadyClock = std::chrono::steady_clock;

int main() {
    GameWindow &gameWindow = GameWindow::getInstance();
    // Render once to show something other, rather than black window
    GameData::setRenderer(gameWindow.getRenderer().getSDLRenderer());
    GameData::load();

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();

    gameLoop();
    gameWindow.quit();
    ImGui_ImplSDLRenderer2_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
    return 0;
}

void gameLoop() {
    UI panels;
    GameWindow &gameWindow = GameWindow::getInstance();
    Renderer &renderer = gameWindow.getRenderer();

#ifdef SDL_HINT_IME_SHOW_UI
    SDL_SetHint(SDL_HINT_IME_SHOW_UI, "1");
#endif

    renderer.swapBuffers();
    panels.push(new MainPanel);
    ImGui_ImplSDL2_InitForSDLRenderer(gameWindow.getSDLWindow(),
                                      renderer.getSDLRenderer());
    ImGui_ImplSDLRenderer2_Init(renderer.getSDLRenderer());
    SteadyClock::time_point frameStart, frameEnd;
    SteadyClock::duration goalFrameDuration =
        std::chrono::nanoseconds(1000000000) / FRAMES_PER_SECOND;
    while (!panels.isDone()) {
        frameStart = SteadyClock::now();

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

        frameEnd = SteadyClock::now();
        SteadyClock::duration executionTime = frameEnd - frameStart;

        if (executionTime < goalFrameDuration) {
            // std::this_thread::sleep_for(goalFrameDuration - executionTime);
        }
    }
}