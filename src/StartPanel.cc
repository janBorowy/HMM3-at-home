#include "StartPanel.h"
#include "UI.h"

StartPanel::StartPanel(const Renderer &renderer) : renderer_(renderer) {
    auto image = GameData::getImage("startScreen.png");
    front_page_.reset(new Sprite(image->getWidth(), image->getHeight(), image));
}

void StartPanel::drawImGui() {}
void StartPanel::step(){};
bool StartPanel::keyDown(SDL_Keycode key, Uint16 mod, bool isNewPress) {
    ui_->setPanelNum(ui_->getPanelNum() - 1);
};
bool StartPanel::mouseButtonDown(int x, int y) {
    ui_->setPanelNum(ui_->getPanelNum() - 1);
};

void StartPanel::draw() { renderer_.drawSprite(0, 0, *front_page_); };