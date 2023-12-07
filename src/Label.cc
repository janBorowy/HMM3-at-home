#include "Label.h"
#include "SDLUtils.h"

Label::Label(std::string initialText, Renderer const &renderer)
    : text_(""),
      image_(),
      renderer_(renderer),
      color_{255, 255, 255},
      x_{0},
      y_{0} {
    updateText(initialText);
}

void Label::updateText(std::string text) {
    text_ = text;
    image_.reset(new Image(renderer_.createTextImage(text, color_)));
};

void Label::setPos(int x, int y) {
    x_ = x;
    y_ = y;
}

void Label::draw() const { renderer_.drawImage(x_, y_, *image_); }