#include <string>
#include <iostream>
#include <SDL2/SDL_image.h>

#include "Engine.h"
#include "SdlFacade.h"

Engine::Engine():
    window_(sdl_facade::createSDLWindow("Heroes of Might & Magic 3",WINDOW_WIDTH, WINDOW_HEIGHT)),
    renderer_(sdl_facade::createSDLRenderer(window_)),
    surface_(SDL_GetWindowSurface(window_)) {
        sdl_facade::initializeSDLImage();
    };

Engine::~Engine() {
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

        //draw game entities

        SDL_RenderPresent(renderer_);
    }
}

// SDL_Texture *Engine::loadTexture(std::string path) const{
//     SDL_Surface *image_surface = IMG_Load(path.c_str());
//     if(image_surface == NULL) {
//         sdl_facade::logSDLError("Could not load surface from " + path);
//     }
//     auto texture = SDL_CreateTextureFromSurface(renderer_, image_surface);
//     if(texture == NULL) {
//         sdl_facade::logSDLError("Could not create texture from " + path);
//     }
//     SDL_FreeSurface(image_surface);
//     return texture;
// }
