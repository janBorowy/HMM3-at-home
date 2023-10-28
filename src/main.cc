#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "engine_core/Engine.h"
#include "SdlFacade.h"

int main() {
    SDL_Init(SDL_INIT_VIDEO);
    sdl_facade::initializeSDLImage();
    Engine engine;
    engine.startLoop();
    IMG_Quit();
    SDL_Quit();
    return 0;
}