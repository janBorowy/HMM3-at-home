#include "Renderer.h"

namespace {
SDL_Renderer *createSDLRenderer(SDL_Window *window) {
    auto renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    return renderer;
}
}  // namespace

Renderer::Renderer(SDL_Window *window)
    : window_(window), renderer_(createSDLRenderer(window)) {}

Renderer::~Renderer() { SDL_DestroyRenderer(renderer_); }

void Renderer::clear() {
    SDL_SetRenderDrawColor(renderer_, 0x00, 0x00, 0x00, 0xFF);
    SDL_RenderClear(renderer_);
}

void Renderer::swapBuffers() { SDL_RenderPresent(renderer_); }

SDL_Renderer *Renderer::getSDLRenderer() const { return renderer_; }

void Renderer::drawEntity(GameEntity const &entity) const {
    auto &sprite = entity.sprite_;
    if (sprite == nullptr) return;
    SDL_Rect rect;
    rect.x = entity.positionX_;
    rect.y = entity.posisitonY_;
    rect.w = sprite->width_;
    rect.h = sprite->height_;
    SDL_RenderCopy(renderer_, sprite->image_->getSDLTexture(), NULL, &rect);
}

void Renderer::drawSprite(int x, int y, Sprite const &sprite) const {
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = sprite.width_;
    rect.h = sprite.height_;
    SDL_RenderCopy(renderer_, sprite.image_->getSDLTexture(), NULL, &rect);
}

void Renderer::drawTexture(int x, int y, int width, int height,
                           SDL_Texture *texture) const {
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = width;
    rect.h = height;
    SDL_RenderCopy(renderer_, texture, NULL, &rect);
}

void Renderer::setColor(Uint8 r, Uint8 g, Uint8 b) {
    SDL_SetRenderDrawColor(renderer_, r, g, b, 0xFF);
}