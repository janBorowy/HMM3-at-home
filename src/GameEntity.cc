#include "GameData.h"
#include "GameEntity.h"

GameEntity::GameEntity(std::string spriteIndex, unsigned short initX,
                       unsigned short initY, unsigned short width,
                       unsigned short height)
    : sprite_(), positionX_(initX), posisitonY_(initY) {
    auto image = GameData::getImage(spriteIndex);
    sprite_.reset(new Sprite(width, height, image));
}

void GameEntity::changeSprite(std::string spriteIndex) {
    auto image = GameData::getImage(spriteIndex);
    sprite_.reset(new Sprite(sprite_->width_, sprite_->height_, image));
}