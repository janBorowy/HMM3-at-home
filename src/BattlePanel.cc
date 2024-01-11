#include "BattlePanel.h"
#include <array>
#include <fstream>
#include <memory>
#include <string>
#include "AlivePlayer.h"
#include "Battle.h"
#include "HeroResources.h"
#include "Label.h"
#include "MainPanel.h"
#include "Soldier.h"
#include "SoldierTypes.h"
#include "Sprite.h"
#include "UI.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_sdlrenderer2.h"

constexpr int GRID_W = 50;
constexpr int GRID_H = 50;
constexpr int GRID_X = 100;
constexpr int GRID_Y = 50;
constexpr int GRID_PANEL_WIDTH = 100;
constexpr int GRID_PANEL_HEIGHT = 896;
constexpr int POW_HEIGHT = 80;
constexpr int POW_WIDTH = 40;

const std::array<std::string, 6> soldierTypeStrings{
    "Archer", "Pikeman", "Swordsman", "Minotaur", "Troglodyte", "Beholder"};

BattlePanel::BattlePanel(const Renderer &renderer,
                         std::vector<UnitInfo> &hero_units,
                         std::vector<UnitInfo> &enemy_units)
    : renderer_(renderer),
      x_(GRID_X),
      y_(GRID_Y),
      clicked_col_(10000),
      clicked_row_(10000),
      if_soldier_info_(false),
      battle_(true),
      hero_initial_army_(hero_units),
      button_(renderer_, 134, 86) {
    button_.setPos(GRID_X * 2 + GRID_W * COLS + 20,
                   GRID_Y + GRID_H * (ROWS - 2));
    battle_.setArmy(hero_units, enemy_units);
    battle_.loadArmySprites();
    loadBattleSprites();
}
void BattlePanel::setArmies(std::vector<UnitInfo> &hero_units,
                            std::vector<UnitInfo> &enemy_units) {
    battle_.setArmy(hero_units, enemy_units);
    battle_.loadArmySprites();
}

void BattlePanel::draw() {
    renderer_.drawSprite(0, 0, *battleGroundSprite_);
    renderer_.drawSprite(0, 0, *panel_);
    if (if_soldier_info_) {
        drawSoldierInfo(battle_.getSoldierForInfo());
    }
    button_.draw();

    for (int i = 0; i < COLS; ++i) {
        for (int j = 0; j < ROWS; ++j) {
            renderer_.drawSprite(GRID_X + i * GRID_W, GRID_Y + j * GRID_H,
                                 *emptyFieldSprite_);
        }
    }
    if (clicked_col_ < COLS && clicked_row_ < ROWS) {
        renderer_.drawSprite(GRID_X + clicked_col_ * GRID_W,
                             GRID_Y + clicked_row_ * GRID_H,
                             *selectedFieldSprite_);
    }

    switch (battle_.getState()) {
        case heroTurn:
            drawWalkingDistance(
                battle_.getHeroArmy().at(battle_.getCounter())->getX(),
                battle_.getHeroArmy().at(battle_.getCounter())->getY(),
                battle_.getHeroArmy().at(battle_.getCounter())->getWalk());
            break;
        case enemyTurn:
            drawWalkingDistance(
                battle_.getEnemyArmy().at(battle_.getCounter())->getX(),
                battle_.getEnemyArmy().at(battle_.getCounter())->getY(),
                battle_.getEnemyArmy().at(battle_.getCounter())->getWalk());
            break;
        case won:
            renderer_.drawSprite(300, 875, *wonSprite_);
            break;
        case lost:
            renderer_.drawSprite(300, 875, *lostSprite_);
            break;
    }

    for (auto &i : battle_.getHeroArmy()) {
        if (i->isAlive()) {
            renderer_.drawSprite(
                GRID_X + i->getX() * GRID_W,
                GRID_Y + i->getY() * GRID_H - i->rightSprite_->height_ / 2,
                *i->rightSprite_);
            renderer_.drawImage(
                GRID_X + i->getX() * GRID_W + 2, GRID_Y + i->getY() * GRID_H,
                renderer_.createTextImage(std::to_string(i->get_number()),
                                          {255, 255, 255}));
        } else {
            renderer_.drawSprite(
                GRID_X + i->getX() * GRID_W,
                GRID_Y + i->getY() * GRID_H - i->deadSprite_->height_ / 2,
                *i->deadSprite_);
        }
    }
    for (auto &i : battle_.getEnemyArmy()) {
        if (i->isAlive()) {
            renderer_.drawSprite(
                GRID_X + i->getX() * GRID_W - 5,
                GRID_Y + i->getY() * GRID_H - i->leftSprite_->height_ / 2,
                *i->leftSprite_);
            renderer_.drawImage(
                GRID_X + i->getX() * GRID_W + 40, GRID_Y + i->getY() * GRID_H,
                renderer_.createTextImage(std::to_string(i->get_number()),
                                          {255, 255, 255}));
        } else {
            renderer_.drawSprite(
                GRID_X + i->getX() * GRID_W,
                GRID_Y + i->getY() * GRID_H - i->deadSprite_->height_ / 2,
                *i->deadSprite_);
        }
    }
}

void BattlePanel::loadBattleSprites() {
    auto image = GameData::getImage("rectRed.png");
    selectedFieldSprite_.reset(new Sprite(GRID_W, GRID_H, image));
    image = GameData::getImage("emptyField.png");
    emptyFieldSprite_.reset(new Sprite(GRID_W, GRID_H, image));
    image = GameData::getImage("rectBlue.png");
    blueFieldSprite_.reset(new Sprite(GRID_W, GRID_H, image));
    image = GameData::getImage("rectWhite.png");
    whiteFieldSprite_.reset(new Sprite(GRID_W, GRID_H, image));
    image = GameData::getImage("BattleGround.png");
    battleGroundSprite_.reset(new Sprite(GRID_W * COLS + 2 * GRID_X,
                                         GRID_H * ROWS + 2 * GRID_Y, image));
    image = GameData::getImage("panel.png");
    panel_.reset(new Sprite(image->getWidth(), image->getHeight(), image));
    image = GameData::getImage("hLost.png");
    lostSprite_.reset(new Sprite(image->getWidth(), image->getHeight(), image));
    image = GameData::getImage("hWon.png");
    wonSprite_.reset(new Sprite(image->getWidth(), image->getHeight(), image));
}

bool BattlePanel::mouseButtonDown(int x, int y) {
    if (battle_.getState() == won) {
        hero_initial_army_.clear();
        for (auto &i : battle_.getHeroArmy()) {
            if (i->isAlive()) {
                hero_initial_army_.push_back({i->get_type(), i->get_number()});
            }
        }
        ui_->pop();
        battle_.reset();
        return true;
    }
    if (battle_.getState() == lost) {
        hero_initial_army_.clear();
        ui_->pop();
        battle_.reset();
        return true;
    }

    if (button_.handleIfClicked(x, y)) {
        battle_.handleNextTurn();
        return true;
    }
    if (x > GRID_X && x < GRID_X + GRID_W * COLS && y > GRID_Y &&
        y < GRID_Y + GRID_H * ROWS) {
        auto clickedCol = (x - x_) / GRID_W;
        auto clickedRow = (y - y_) / GRID_H;
        handleMapGridClick(clickedCol, clickedRow);
        return true;
    }
    return false;
}

void BattlePanel::handleMapGridClick(int clickedCol, int clickedRow) {
    if (clickedCol == clicked_col_ && clickedRow == clicked_row_) {
        battle_.battleSpin(clickedCol, clickedRow);
        if_soldier_info_ = false;
    } else if (battle_.setSoldierInfo(clickedCol, clickedRow)) {
        if_soldier_info_ = true;
    } else {
        battle_.battleSpin(clickedCol, clickedRow);
        if_soldier_info_ = false;
    }
    clicked_col_ = clickedCol;
    clicked_row_ = clickedRow;
}

void BattlePanel::drawImGui() {}
void BattlePanel::step(){};
bool BattlePanel::keyDown(SDL_Keycode key, Uint16 mod, bool isNewPress) {
    return false;
};

void BattlePanel::drawWalkingDistance(int x, int y, int distance) {
    for (int temp_x = x - distance; temp_x <= x + distance; ++temp_x) {
        for (int temp_y = y - distance; temp_y <= y + distance; ++temp_y) {
            if (temp_x >= 0 && temp_x < COLS && temp_y >= 0 && temp_y < ROWS) {
                if (std::abs(temp_x - x) + std::abs(temp_y - y) <= distance) {
                    renderer_.drawSprite(GRID_X + temp_x * GRID_W,
                                         GRID_Y + temp_y * GRID_H,
                                         *blueFieldSprite_);
                }
            }
        }
    }
    renderer_.drawSprite(GRID_X + x * GRID_W, GRID_Y + y * GRID_H,
                         *whiteFieldSprite_);
}

void BattlePanel::drawSoldierInfo(const SoldierPtr &soldier) {
    SDL_Rect rect;
    rect.x = 1020;
    rect.y = 80;
    rect.w = 200;
    rect.h = 280;
    if (soldier->isAlive()) {
        renderer_.drawSprite(*soldier->rightSprite_, rect);
    } else {
        renderer_.drawSprite(*soldier->deadSprite_, rect);
    }
    std::string initial_string =
        "Name: " + soldierTypeStrings[soldier->get_type()];
    Label label(initial_string, renderer_);
    label.setPos(1030, 390);
    label.draw();

    label.updateText("Unit health: " + std::to_string(soldier->getHealth()));
    label.setPos(1030, 410);
    label.draw();

    label.updateText("Current health: " +
                     std::to_string(soldier->getCurrentHealth()));
    label.setPos(1030, 430);
    label.draw();

    label.updateText("Unit damage: " + std::to_string(soldier->getDamage()));
    label.setPos(1030, 450);
    label.draw();

    label.updateText("Number of units: " +
                     std::to_string(soldier->get_number()));
    label.setPos(1030, 470);
    label.draw();
}
