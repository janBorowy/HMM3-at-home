#include "GameEntity.h"
#include "Hero.h"
#include "MapExtrinsic.h"

class HeroExtrinsic {
    Hero hero_;
    MapExtrinsic const &map_;
    Sprite sprite_;

   public:
    HeroExtrinsic(int initCol, int initRow, MapExtrinsic const &map);
    Hero &hero();
    void draw(Renderer const &renderer) const;
};