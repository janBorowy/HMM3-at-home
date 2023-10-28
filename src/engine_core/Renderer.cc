#include "Renderer.h"
#include "SdlFacade.h"

Renderer::Renderer():
    window_(std::unique_ptr<Window>(new Window())),
    renderer_(window_->createSDLRenderer()) {}

Renderer::~Renderer() {
    SDL_DestroyRenderer(renderer_);
}

void Renderer::clear() {
    SDL_RenderClear(renderer_);
}

void Renderer::swapBuffers() {
    SDL_RenderPresent(renderer_);
}

SDL_Renderer *Renderer::getSDLRenderer() {
    return renderer_;
}

void Renderer::renderSprite(const std::unique_ptr<Sprite> &sprite,
    int x, int y) {
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = sprite->getWidth();
    rect.h = sprite->getHeight();
    SDL_RenderCopy(renderer_, sprite->getSDLTexture(), NULL, &rect);
}