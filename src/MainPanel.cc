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

MainPanel::MainPanel(Renderer const &renderer)
    : Panel(),
      renderer_(renderer),
      map_{GRID_X, GRID_Y, GRID_PANEL_WIDTH, GRID_PANEL_HEIGHT,
           loadMap(
               50, 50,
               "/home/janek/workspace/Heroes-3-clone/resource/map1.hmm3map")},
      staminaResourceLabel_("Stamina: ", renderer),
      goldResourceLabel_("Gold: ", renderer),
      woodResourceLabel_("Wood: ", renderer),
      oreResourceLabel_("Ore: ", renderer),
      selection_(map_.fieldWidth(), map_.fieldHeight(), renderer),
      playerHero_(1, 1, map_) {
    goldResourceLabel_.setPos(50, 950);
    staminaResourceLabel_.setPos(150, 950);
    woodResourceLabel_.setPos(300, 950);
    oreResourceLabel_.setPos(450, 950);
}
void MainPanel::step() {}
void MainPanel::draw() {
    map_.drawFields(renderer_);
    playerHero_.draw(renderer_);
    map_.accept(&selection_);
    goldResourceLabel_.draw();
    staminaResourceLabel_.draw();
    woodResourceLabel_.draw();
    oreResourceLabel_.draw();
}
void MainPanel::drawImGui() {
    ImGui_ImplSDLRenderer2_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    auto io = ImGui::GetIO();
    ImGui::NewFrame();
    {
        ImGui::Begin("Debug");
        ImGui::Text("FPS: %1.f", io.Framerate);
        ImGui::Text("Camera (%d,%d)", map_.getCameraPosition().first,
                    map_.getCameraPosition().second);
        ImGui::Text("Selection COL: %d, ROW: %d", selection_.col(),
                    selection_.row());
        ImGui::Text("PLAYER STATS");
        ImGui::Text("Stamina: %d", playerHero_.hero().resources().stamina());
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
    if (x > GRID_X && x < GRID_X + GRID_PANEL_WIDTH && y > GRID_Y &&
        y < GRID_Y + GRID_PANEL_HEIGHT) {
        auto clickedCol = (x - map_.x()) / map_.fieldWidth() + 1;
        auto clickedRow = (y - map_.y()) / map_.fieldHeight() + 1;
        handleMapGridClick(clickedCol, clickedRow);
        return true;
    }
    return false;
}

void MainPanel::handleMapGridClick(int clickedCol, int clickedRow) {
    auto cameraPos = map_.getCameraPosition();
    auto mapCol = clickedCol + cameraPos.first;
    auto mapRow = clickedRow + cameraPos.second;
    if (selection_.col() == mapCol && selection_.row() == mapRow &&
        playerHero_.hero().canMove({mapCol, mapRow}, map_.gameMap())) {
        handleMapGridMove(mapCol, mapRow);
    } else {
        handleMapGridSelect(mapCol, mapRow);
    }
}

void MainPanel::handleMapGridSelect(int mapCol, int mapRow) {
    selection_.setPosition(mapCol, mapRow);
    selection_.canMove(
        playerHero_.hero().canMove({mapCol, mapRow}, map_.gameMap()));
    selection_.visible(true);
}

void MainPanel::handleMapGridMove(int mapCol, int mapRow) {
    playerHero_.hero().move({mapCol, mapRow}, map_.gameMap());
    selection_.visible(false);
}