#include "DifficultyButton.h"

DifficultyButton::DifficultyButton(const Renderer &renderer, int width,
                                   int height, Difficulty difficulty)
    : Button("Initial txt", renderer, width, height), difficulty_(difficulty) {
    switch (difficulty_) {
        case easy:
            updateText("Easy");
            break;
        case normal:
            updateText("Normal");
            break;
        case hard:
            updateText("Hard");
            break;
    }
}

void DifficultyButton::handleClick() {}
