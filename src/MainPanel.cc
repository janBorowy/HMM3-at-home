#include <fstream>
#include "MainPanel.h"
#include "MapParser.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_sdlrenderer2.h"

constexpr int GRID_X = 50;
constexpr int GRID_Y = 50;
constexpr int GRID_PANEL_WIDTH = 1000;
constexpr int GRID_PANEL_HEIGHT = 896;

namespace {
GameMap loadMap(int width, int height, std::string filename) {
    std::ifstream file(filename);
    MapParser parser(50, 50);
    return parser.parse(file);
}
}  // namespace

MainPanel::MainPanel()
    : Panel(),
      map_{GRID_X, GRID_Y, GRID_PANEL_WIDTH, GRID_PANEL_HEIGHT,
           loadMap(
               50, 50,
               "/home/janek/workspace/Heroes-3-clone/resource/map1.hmm3map")} {}
void MainPanel::step() {}
void MainPanel::draw(Renderer const &renderer) { map_.drawFields(renderer); }
void MainPanel::drawImGui(Renderer const &renderer) {
    ImGui_ImplSDLRenderer2_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    auto io = ImGui::GetIO();
    ImGui::NewFrame();
    {
        ImGui::Begin("Debug");
        ImGui::Text("FPS: %1.f", io.Framerate);
        ImGui::Text("CAMERA X: %d Y: %d", map_.getCameraPosition().first,
                    map_.getCameraPosition().second);
        ImGui::End();
    }
    ImGui::Render();
    ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData());
}
bool MainPanel::keyDown(SDL_Keycode key, Uint16 mod, bool isNewPress) {
    if (key == SDLK_RIGHT) {
        map_.moveCameraBy({1, 0});
        return true;
    }
    if (key == SDLK_LEFT) {
        map_.moveCameraBy({-1, 0});
        return true;
    }

    if (key == SDLK_UP) {
        map_.moveCameraBy({0, -1});
        return true;
    }

    if (key == SDLK_DOWN) {
        map_.moveCameraBy({0, 1});
        return true;
    }

    return false;
}

bool MainPanel::mouseButtonDown(int x, int y) {
    // if (x > GRID_X && x < GRID_X + GRID_PANEL_WIDTH && y > GRID_Y &&
    //     y < GRID_Y + GRID_PANEL_HEIGHT) {
    //     mapGrid_.handleClick(x, y);
    //     return true;
    // }
    return false;
}