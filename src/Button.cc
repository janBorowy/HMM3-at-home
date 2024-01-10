#include "Button.h"
#include "GameData.h"

Button::Button(std::string text, const Renderer &renderer, int width,
               int height)
    : Label(text, renderer),
      borderSprite_(width, height, GameData::getImage("longboard.png")),
      width_(width),
      height_(height) {}
Button::Button(std::string text, const Renderer &renderer,
               std::string image_name, int width, int height)
    : Label(text, renderer),
      borderSprite_(width, height, GameData::getImage(image_name)),
      width_(width),
      height_(height) {}

bool Button::handleIfClicked(int cursorX, int cursorY) {
    if (cursorX > x_ && cursorX < x_ + width_ && cursorY > y_ &&
        cursorY < y_ + height_) {
        handleClick();
        return true;
    }
    return false;
}

void Button::draw() const {
    renderer_.drawSprite(x_, y_, borderSprite_);
    renderer_.drawImage(x_ + width_ / 2 - (image_->getWidth() / 2),
                        y_ + height_ / 2 - (image_->getHeight() / 2), *image_);
}