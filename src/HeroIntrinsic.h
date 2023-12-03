#include <utility>
#include "HeroResources.h"
using Position = std::pair<int, int>;
class HeroIntrinsic {
    HeroResources resources_;
    Position position_;

   public:
    HeroIntrinsic();
};