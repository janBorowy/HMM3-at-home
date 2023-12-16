#pragma once

class MapExtrinsic;
class MapVisitator {
   public:
    virtual void visit(const MapExtrinsic &map) = 0;
};