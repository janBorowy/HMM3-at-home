#include "StartPanel.h"
#include "MainPanel.h"
#include "UI.h"

StartPanel::StartPanel(const Renderer &renderer) : renderer_(renderer) {
    auto image = GameData::getImage("startScreen.png");
    front_page_.reset(new Sprite(image->getWidth(), image->getHeight(), image));
}

void StartPanel::drawImGui() {}
void StartPanel::step(){};
bool StartPanel::keyDown(SDL_Keycode key, Uint16 mod, bool isNewPress) {
    ui_->push(new MainPanel(renderer_));
    return true;
};
bool StartPanel::mouseButtonDown(int x, int y) {
    ui_->push(new MainPanel(renderer_));
    return true;
};

void StartPanel::draw() { renderer_.drawSprite(0, 0, *front_page_); };