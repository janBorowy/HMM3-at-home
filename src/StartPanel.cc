#include "StartPanel.h"
#include "MainPanel.h"
#include "UI.h"

StartPanel::StartPanel(const Renderer &renderer)
    : renderer_(renderer),
      easy_button_(renderer, 300, 100, easy),
      normal_button_(renderer, 300, 100, normal),
      hard_button_(renderer, 300, 100, hard) {
    auto image = GameData::getImage("startScreen.png");
    front_page_.reset(new Sprite(image->getWidth(), image->getHeight(), image));
    easy_button_.setPos(650, 400);
    normal_button_.setPos(650, 500);
    hard_button_.setPos(650, 600);
}

void StartPanel::drawImGui() {}
void StartPanel::step(){};
bool StartPanel::keyDown(SDL_Keycode key, Uint16 mod, bool isNewPress) {
    return true;
};
bool StartPanel::mouseButtonDown(int x, int y) {
    if (easy_button_.handleIfClicked(x, y)) {
        auto mainBattlePtr = new MainPanel(renderer_);
        mainBattlePtr->setDifficulty(easy);
        auto ui = ui_;
        ui->pop();
        ui->push(mainBattlePtr);
        return true;
    }
    if (normal_button_.handleIfClicked(x, y)) {
        auto mainBattlePtr = new MainPanel(renderer_);
        mainBattlePtr->setDifficulty(normal);
        auto ui = ui_;
        ui->pop();
        ui->push(mainBattlePtr);
        return true;
    }
    if (hard_button_.handleIfClicked(x, y)) {
        auto mainBattlePtr = new MainPanel(renderer_);
        mainBattlePtr->setDifficulty(hard);
        auto ui = ui_;
        ui->pop();
        ui->push(mainBattlePtr);
        return true;
    }
    return true;
};

void StartPanel::draw() {
    renderer_.drawSprite(0, 0, *front_page_);
    easy_button_.draw();
    normal_button_.draw();
    hard_button_.draw();
};