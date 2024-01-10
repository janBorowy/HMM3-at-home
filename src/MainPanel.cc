#include "MainPanel.h"
#include <fstream>
#include "BattlePanel.h"
#include "HeroResources.h"
#include "MapObject.h"
#include "MapParser.h"
#include "Soldier.h"
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

MainPanel::MainPanel(const Renderer &renderer)
    : Panel(),
      renderer_(renderer),
      map_{GRID_X, GRID_Y, GRID_PANEL_WIDTH, GRID_PANEL_HEIGHT,
           loadMap(50, 50, "resources/map1.hmm3map")},
      staminaResourceLabel_("Stamina: ", renderer),
      goldResourceLabel_("Gold: ", renderer),
      woodResourceLabel_("Wood: ", renderer),
      oreResourceLabel_("Ore: ", renderer),
      turnLabel_("Turn: ", renderer),
      unitInfoLabel_("Units: ", renderer),
      selection_(map_.fieldWidth(), map_.fieldHeight(), renderer),
      playerHero_(1, 1, map_),
      turnManager_(playerHero_.hero()),
      nextTurnButton_(renderer_, 300, 100, turnManager_) {
    staminaResourceLabel_.setPos(50, 950);
    goldResourceLabel_.setPos(200, 950);
    woodResourceLabel_.setPos(350, 950);
    oreResourceLabel_.setPos(500, 950);
    unitInfoLabel_.setPos(GRID_X + GRID_PANEL_WIDTH + 30, GRID_Y);
    turnLabel_.setPos(GRID_X + GRID_PANEL_WIDTH + 30,
                      GRID_PANEL_HEIGHT + GRID_Y);
    nextTurnButton_.setPos(GRID_X + GRID_PANEL_WIDTH + 30,
                           GRID_PANEL_HEIGHT + GRID_Y - 115);
}
void MainPanel::step() {}
void MainPanel::draw() {
    map_.draw(renderer_);
    playerHero_.draw(renderer_);
    map_.accept(&selection_);
    updateAndDrawLabels();
    nextTurnButton_.draw();
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
        ImGui::Text("Position: (%d, %d)", playerHero_.hero().position().first,
                    playerHero_.hero().position().second);
        ImGui::Text("Stamina: %d", playerHero_.hero().resources().stamina());
        ImGui::Text("Gold: %d", playerHero_.hero().resources().gold());
        ImGui::Text("Wood: %d", playerHero_.hero().resources().wood());
        ImGui::Text("Ore: %d", playerHero_.hero().resources().ore());
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
    if (nextTurnButton_.handleIfClicked(x, y)) {
        return true;
    }
    return false;
}

void MainPanel::handleMapGridClick(int clickedCol, int clickedRow) {
    auto cameraPos = map_.getCameraPosition();
    auto mapCol = clickedCol + cameraPos.first;
    auto mapRow = clickedRow + cameraPos.second;
    if (playerHero_.hero().position() == Position{clickedCol, clickedRow}) {
        // Show hero info?
        return;
    }
    if (selection_.col() == mapCol && selection_.row() == mapRow &&
        playerHero_.hero().canMove({mapCol, mapRow}, map_.gameMap(), true)) {
        handleMapGridMove(mapCol, mapRow);
        return;
    } else {
        handleMapGridSelect(mapCol, mapRow);
        return;
    }
}

void MainPanel::handleMapGridSelect(int mapCol, int mapRow) {
    selection_.setPosition(mapCol, mapRow);
    auto canMoveThere =
        playerHero_.hero().canMove({mapCol, mapRow}, map_.gameMap(), true);
    selection_.canMove(canMoveThere);
    if (canMoveThere) {
        selection_.setMovementIndicators(playerHero_.hero().getMovementPath(
            {mapCol, mapRow}, map_.gameMap()));
    };
    selection_.visible(true);
}

void MainPanel::handleMapGridMove(int mapCol, int mapRow) {
    bool if_battle = false;
    playerHero_.hero().move({mapCol, mapRow}, map_.gameMap());
    if (map_.gameMap().at({mapCol, mapRow}).object_.type() ==
        MapObject::Type::ENEMY) {
        setBattle(mapCol, mapRow);
    }
    playerHero_.hero().interactWith(map_.gameMap(), {mapCol, mapRow});
    selection_.visible(false);
}

void MainPanel::setBattle(int mapCol, int mapRow) {
    std::vector<UnitInfo> e_units;

    switch (map_.gameMap().at(mapCol, mapRow).object_.type()) {
        case MapObject::ENEMY:
            int number = map_.gameMap().at(mapCol, mapRow).object_.value();

            e_units.push_back(UnitInfo(TROGLODYTE, number));
            e_units.push_back(UnitInfo(TROGLODYTE, number));
            e_units.push_back(UnitInfo(TROGLODYTE, number));
            break;
    }
    auto battlePanelPtr = new BattlePanel(renderer_);
    battlePanelPtr->setArmies(playerHero_.hero().resources().getUnits(),
                              e_units);
    ui_->push(battlePanelPtr);
}

void MainPanel::updateAndDrawLabels() {
    std::string goldLabelText = "Gold: ";
    goldLabelText += std::to_string(playerHero_.hero().resources().gold());
    goldResourceLabel_.updateText(goldLabelText);
    goldResourceLabel_.draw();

    std::string staminaLabelText = "Stamina: ";
    staminaLabelText +=
        std::to_string(playerHero_.hero().resources().stamina());
    staminaResourceLabel_.updateText(staminaLabelText);
    staminaResourceLabel_.draw();

    std::string woodLabelText = "Wood: ";
    woodLabelText += std::to_string(playerHero_.hero().resources().wood());
    woodResourceLabel_.updateText(woodLabelText);
    woodResourceLabel_.draw();

    std::string oreLabelText = "Ore: ";
    oreLabelText += std::to_string(playerHero_.hero().resources().ore());
    oreResourceLabel_.updateText(oreLabelText);
    oreResourceLabel_.draw();

    std::string turnLabelText = "Turn: ";
    turnLabelText += std::to_string(turnManager_.currentTurn());
    turnLabel_.updateText(turnLabelText);
    turnLabel_.draw();

    std::string unitInfoLabelText = "Units - ";
    for (auto unitInfo : playerHero_.hero().resources().getUnits()) {
        unitInfoLabelText += unitInfo.infoString() + "  ";
    }
    unitInfoLabel_.updateText(unitInfoLabelText);
    unitInfoLabel_.draw();
}