#include "BattlePanel.h"
#include <fstream>
#include <string>
#include "AlivePlayer.h"
#include "Battle.h"
#include "HeroResources.h"
#include "Soldier.h"
#include "SoldierTypes.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_sdlrenderer2.h"

constexpr int GRID_WIDTH = 50;
constexpr int GRID_HEIGHT = 50;
constexpr int GRID_X = 150;
constexpr int GRID_Y = 50;
constexpr int GRID_PANEL_WIDTH = 1000;
constexpr int GRID_PANEL_HEIGHT = 896;
constexpr int POW_HEIGHT = 80;
constexpr int POW_WIDTH = 40;

BattlePanel::BattlePanel(const Renderer &renderer)
    : renderer_(renderer),
      x_(GRID_X),
      y_(GRID_Y),
      clicked_col_(10000),
      clicked_row_(10000),
      battle_(true),
      button_(renderer_, 134, 86) {
    button_.setPos(GRID_X + GRID_WIDTH * COLS + 2,
                   GRID_Y + GRID_HEIGHT * (ROWS - 2));
    std::vector<UnitInfo> h_units;
    std::vector<UnitInfo> e_units;
    h_units.push_back(UnitInfo(ARCHER, 5));
    h_units.push_back(UnitInfo(TROGLODYTE, 10));
    h_units.push_back(UnitInfo(SWORDSMAN, 5));

    e_units.push_back(UnitInfo(MINOTAUR, 2));
    e_units.push_back(UnitInfo(BEHOLDER, 5));
    e_units.push_back(UnitInfo(TROGLODYTE, 20));
    //  e_units.push_back(UnitInfo(TROGLODYTE, 10));
    battle_.setArmy(h_units, e_units);
    battle_.loadArmySprites();

    loadBattleSprites();
}

void BattlePanel::draw() {
    renderer_.drawSprite(0, 0, *battleGroundSprite_);
    button_.draw();

    for (int i = 0; i < COLS; ++i) {
        for (int j = 0; j < ROWS; ++j) {
            renderer_.drawSprite(GRID_X + i * GRID_WIDTH,
                                 GRID_Y + j * GRID_HEIGHT, *emptyFieldSprite_);
        }
    }
    if (clicked_col_ < COLS && clicked_row_ < ROWS) {
        renderer_.drawSprite(GRID_X + clicked_col_ * GRID_WIDTH,
                             GRID_Y + clicked_row_ * GRID_HEIGHT,
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
            break;
        case lost:
            break;
    }

    for (auto &i : battle_.getHeroArmy()) {
        if (i->isAlive()) {
            renderer_.drawSprite(
                GRID_X + i->getX() * GRID_WIDTH,
                GRID_Y + i->getY() * GRID_HEIGHT - i->rightSprite_->height_ / 2,
                *i->rightSprite_);
            renderer_.drawImage(
                GRID_X + i->getX() * GRID_WIDTH + 2,
                GRID_Y + i->getY() * GRID_HEIGHT,
                renderer_.createTextImage(std::to_string(i->get_number()),
                                          {255, 255, 255}));
        } else {
            renderer_.drawSprite(
                GRID_X + i->getX() * GRID_WIDTH,
                GRID_Y + i->getY() * GRID_HEIGHT - i->deadSprite_->height_ / 2,
                *i->deadSprite_);
        }
    }
    for (auto &i : battle_.getEnemyArmy()) {
        if (i->isAlive()) {
            renderer_.drawSprite(
                GRID_X + i->getX() * GRID_WIDTH - 5,
                GRID_Y + i->getY() * GRID_HEIGHT - i->leftSprite_->height_ / 2,
                *i->leftSprite_);
            renderer_.drawImage(
                GRID_X + i->getX() * GRID_WIDTH + 40,
                GRID_Y + i->getY() * GRID_HEIGHT,
                renderer_.createTextImage(std::to_string(i->get_number()),
                                          {255, 255, 255}));
        } else {
            renderer_.drawSprite(
                GRID_X + i->getX() * GRID_WIDTH,
                GRID_Y + i->getY() * GRID_HEIGHT - i->deadSprite_->height_ / 2,
                *i->deadSprite_);
        }
    }
}

void BattlePanel::loadBattleSprites() {
    auto image = GameData::getImage("rectRed.png");
    selectedFieldSprite_.reset(new Sprite(GRID_WIDTH, GRID_HEIGHT, image));
    image = GameData::getImage("emptyField.png");
    emptyFieldSprite_.reset(new Sprite(GRID_WIDTH, GRID_HEIGHT, image));
    image = GameData::getImage("rectBlue.png");
    blueFieldSprite_.reset(new Sprite(GRID_WIDTH, GRID_HEIGHT, image));
    image = GameData::getImage("rectWhite.png");
    whiteFieldSprite_.reset(new Sprite(GRID_WIDTH, GRID_HEIGHT, image));
    image = GameData::getImage("BattleGround.png");
    battleGroundSprite_.reset(new Sprite(GRID_WIDTH * COLS + 2 * GRID_X,
                                         GRID_HEIGHT * ROWS + 2 * GRID_Y,
                                         image));
}

bool BattlePanel::mouseButtonDown(int x, int y) {
    if (button_.handleIfClicked(x, y)) {
        battle_.handleNextTurn();
        return true;
    }
    if (x > GRID_X && x < GRID_X + GRID_WIDTH * COLS && y > GRID_Y &&
        y < GRID_Y + GRID_HEIGHT * ROWS) {
        auto clickedCol = (x - x_) / GRID_WIDTH;
        auto clickedRow = (y - y_) / GRID_HEIGHT;
        handleMapGridClick(clickedCol, clickedRow);
        return true;
    }
    return false;
}

void BattlePanel::handleMapGridClick(int clickedCol, int clickedRow) {
    battle_.battleSpin(clickedCol, clickedRow);
    clicked_col_ = clickedCol;
    clicked_row_ = clickedRow;
    // std::cout << clickedCol << "\n" << clickedRow << "\n";
}

void BattlePanel::drawImGui() {}
void BattlePanel::step(){};
bool BattlePanel::keyDown(SDL_Keycode key, Uint16 mod, bool isNewPress){};

void BattlePanel::drawWalkingDistance(int x, int y, int distance) {
    for (int temp_x = x - distance; temp_x <= x + distance; ++temp_x) {
        for (int temp_y = y - distance; temp_y <= y + distance; ++temp_y) {
            if (temp_x >= 0 && temp_x < COLS && temp_y >= 0 && temp_y < ROWS) {
                if (std::abs(temp_x - x) + std::abs(temp_y - y) <= distance) {
                    renderer_.drawSprite(GRID_X + temp_x * GRID_WIDTH,
                                         GRID_Y + temp_y * GRID_HEIGHT,
                                         *blueFieldSprite_);
                }
            }
        }
    }
    renderer_.drawSprite(GRID_X + x * GRID_WIDTH, GRID_Y + y * GRID_HEIGHT,
                         *whiteFieldSprite_);
}