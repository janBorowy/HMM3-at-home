#pragma once
#include <string>
#include <unordered_map>
#include "Image.h"

using ImageMap = std::unordered_map<std::string, ImagePtr>;

class GameData {
    static void loadFromPng(std::string path, SDL_Renderer *renderer);
    static SDL_Renderer *renderer_;
    static ImageMap imageMap;

   public:
    static void setRenderer(SDL_Renderer *renderer);
    static ImagePtr getImage(std::string index);
    static void load();
    static void reg(std::string index, Image *image);
};