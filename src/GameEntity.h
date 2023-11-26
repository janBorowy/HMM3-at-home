#pragma once
#include <string>
#include "Sprite.h"

class Renderer;

class GameEntity {
    friend Renderer;
    SpriteUPtr sprite_;

   public:
    GameEntity(std::string spriteIndex, unsigned short initX,
               unsigned short initY, unsigned short width,
               unsigned short height);
    void changeSprite(std::string spriteIndex);
    unsigned short positionX_;
    unsigned short posisitonY_;
};