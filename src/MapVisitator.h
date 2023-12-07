#pragma once

class MapExtrinsic;
class MapVisitator {
   public:
    virtual void visit(MapExtrinsic const &map) = 0;
};