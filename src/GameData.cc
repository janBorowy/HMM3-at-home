#include <filesystem>
#include "GameData.h"
#include "SDLUtils.h"

namespace fs = std::filesystem;

SDL_Renderer *GameData::renderer_ = nullptr;
ImageMap GameData::imageMap = ImageMap();

void GameData::loadFromPng(std::string path, SDL_Renderer *renderer) {
    SDL_Surface *image_surface = IMG_Load(path.c_str());
    if (image_surface == NULL) {
        SDLError::checkSDLError();
        return;
    }
    auto texture = SDL_CreateTextureFromSurface(renderer, image_surface);
    if (texture == NULL) {
        SDL_FreeSurface(image_surface);
        SDLError::checkSDLError();
        return;
    }
    int width = image_surface->w;
    int height = image_surface->h;
    SDL_FreeSurface(image_surface);
    reg(fs::path(path).filename(), new Image(texture, width, height));
}

void GameData::load() {
    auto directory = fs::directory_entry("../images");
    for (const auto &dir_entry : fs::directory_iterator{directory}) {
        if (dir_entry.is_regular_file()) {
            loadFromPng(dir_entry.path(), renderer_);
        }
    }
}

void GameData::setRenderer(SDL_Renderer *renderer) { renderer_ = renderer; }

void GameData::reg(std::string index, Image *image) {
    imageMap[index] = ImagePtr(image);
}

ImagePtr GameData::getImage(std::string index) { return imageMap[index]; }