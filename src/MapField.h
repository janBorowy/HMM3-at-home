#pragma once
class MapField {
    bool movable_;

   public:
    MapField();
    MapField(int val_, bool movable_);
    int val_;
};