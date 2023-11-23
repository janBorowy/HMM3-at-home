#include "GameData.h"
#include "GameEntity.h"

GameEntity::GameEntity(std::string spriteIndex, unsigned short initX,
                       unsigned short initY, unsigned short width,
                       unsigned short height)
    : sprite_(), positionX_(initX), posisitonY_(initY) {
    auto image = GameData::getImage(spriteIndex);
    sprite_.reset(new Sprite(width, height, image));
}