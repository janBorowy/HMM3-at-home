#include "GameEntity.h"
#include "Hero.h"
#include "MapExtrinsic.h"

class HeroExtrinsic {
    Hero hero_;
    const MapExtrinsic &map_;
    Sprite sprite_;

   public:
    HeroExtrinsic(int initCol, int initRow, const MapExtrinsic &map);
    Hero &hero();
    void draw(const Renderer &renderer) const;
};