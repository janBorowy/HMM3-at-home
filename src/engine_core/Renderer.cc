#include "Renderer.h"
#include "SdlFacade.h"

Renderer::Renderer()
    : window_(std::unique_ptr<Window>(new Window())),
      renderer_(window_->createSDLRenderer()) {}

Renderer::~Renderer() { SDL_DestroyRenderer(renderer_); }

void Renderer::clear() {
    SDL_SetRenderDrawColor(renderer_, 0x00, 0x00, 0x00, 0xFF);
    SDL_RenderClear(renderer_);
}

void Renderer::swapBuffers() { SDL_RenderPresent(renderer_); }

SDL_Renderer *Renderer::getSDLRenderer() { return renderer_; }

void Renderer::renderSprite(std::shared_ptr<Sprite> const &sprite, int x,
                            int y) {
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = sprite->getWidth();
    rect.h = sprite->getHeight();
    SDL_RenderCopy(renderer_, sprite->getSDLTexture(), NULL, &rect);
}

void Renderer::drawLine(int startX, int startY, int endX, int endY) {
    SDL_RenderDrawLine(renderer_, startX, startY, endX, endY);
}

void Renderer::setColor(Uint8 r, Uint8 g, Uint8 b) {
    SDL_SetRenderDrawColor(renderer_, r, g, b, 0xFF);
}