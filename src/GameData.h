#include <string>
#include <unordered_map>
#include "Image.h"

using ImageMap = std::unordered_map<std::string, ImageUPtr>;

class GameData {
    static void loadFromPng(std::string path, SDL_Renderer *renderer);
    static SDL_Renderer *renderer_;
    static std::unordered_map<std::string, ImageUPtr> imageMap;

   public:
    static void setRenderer(SDL_Renderer *renderer);
    static Image const &getImage(std::string index);
    static void load();
    static void reg(std::string index, Image *image);
};