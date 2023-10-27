#include <string>
#include <iostream>
#include <SDL2/SDL_image.h>

#include "Engine.h"

namespace SDL_UTILS{

    void logSDLError(std::string message) {
        std::cout << message << ": " << SDL_GetError() << std::endl;
    }

    SDL_Window *createSDLWindow() {
        auto window = SDL_CreateWindow("Heroes of Might & Magic 3",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        SDL_WINDOW_SHOWN);

        if(window == NULL) {
            logSDLError("Could not initialize window");
        }
        return window;
    }

    SDL_Renderer *createSDLRenderer(SDL_Window *window) {
        auto renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

        if(renderer == NULL) {
            logSDLError("Could not initialize renderer");
        }
        return renderer;
    }

    void initializeSDLImage() {
        int flags = IMG_INIT_PNG;
        if(!(IMG_Init(flags)) & flags) {
            logSDLError("Could not initialize image library");
        }
    }

}

Engine::Engine():
    window_(SDL_UTILS::createSDLWindow()),
    renderer_(SDL_UTILS::createSDLRenderer(window_)),
    surface_(SDL_GetWindowSurface(window_)) {
        SDL_UTILS::initializeSDLImage();
        texture_ = loadTexture("/home/janek/workspace/Heroes-3-clone/.secret/zadanie.png");
        if(texture_ == NULL) {
            SDL_UTILS::logSDLError("Could not load texture");
        } 
    };

Engine::~Engine() {
    SDL_DestroyTexture(texture_);
    SDL_DestroyRenderer(renderer_);
    SDL_DestroyWindow(window_);
    
    IMG_Quit();
    SDL_Quit();
}

void Engine::startLoop() {
    bool quit = false;
    SDL_Event e;
    while(!quit) {
        while(SDL_PollEvent(&e) != 0 ) {
            if(e.type == SDL_QUIT) {
                quit = true;
            }
        }

        SDL_RenderClear(renderer_);
        SDL_RenderCopy(renderer_, texture_, NULL, NULL);
        SDL_RenderPresent(renderer_);
    }
}

SDL_Texture *Engine::loadTexture(std::string path) const{
    SDL_Surface *image_surface = IMG_Load(path.c_str());
    if(image_surface == NULL) {
        SDL_UTILS::logSDLError("Could not load surface from " + path);
    }
    auto texture = SDL_CreateTextureFromSurface(renderer_, image_surface);
    if(texture == NULL) {
        SDL_UTILS::logSDLError("Could not create texture from " + path);
    }
    SDL_FreeSurface(image_surface);
    return texture;
}
