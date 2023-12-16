#include "Renderer.h"
#include "SDLUtils.h"

constexpr std::string_view VERA_FONT_PATH = "resources/Vera.ttf";

namespace {
SDL_Renderer *createSDLRenderer(SDL_Window *window) {
    auto renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    return renderer;
}

TTF_Font *openFont(const std::string &path) {
    auto font = TTF_OpenFont(path.c_str(), 14);
    // Maybe add some handling in case TTF_OpenFont fails
    return font;
}
}  // namespace

Renderer::Renderer(SDL_Window *window)
    : window_(window),
      renderer_(createSDLRenderer(window)),
      font_(openFont({VERA_FONT_PATH.begin(), VERA_FONT_PATH.end()})) {}

Renderer::~Renderer() { SDL_DestroyRenderer(renderer_); }

void Renderer::clear() {
    SDL_SetRenderDrawColor(renderer_, 0x00, 0x00, 0x00, 0xFF);
    SDL_RenderClear(renderer_);
}

void Renderer::swapBuffers() { SDL_RenderPresent(renderer_); }

SDL_Renderer *Renderer::getSDLRenderer() const { return renderer_; }

void Renderer::drawEntity(const GameEntity &entity) const {
    auto &sprite = entity.sprite_;
    if (sprite == nullptr) return;
    SDL_Rect rect;
    rect.x = entity.positionX_;
    rect.y = entity.posisitonY_;
    rect.w = sprite->width_;
    rect.h = sprite->height_;
    SDL_RenderCopy(renderer_, sprite->image_->getSDLTexture(), NULL, &rect);
}

void Renderer::drawSprite(int x, int y, const Sprite &sprite) const {
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = sprite.width_;
    rect.h = sprite.height_;
    SDL_RenderCopy(renderer_, sprite.image_->getSDLTexture(), NULL, &rect);
}

void Renderer::drawImage(int x, int y, const Image &image) const {
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = image.getWidth();
    rect.h = image.getHeight();
    SDL_RenderCopy(renderer_, image.getSDLTexture(), NULL, &rect);
}

void Renderer::setColor(Uint8 r, Uint8 g, Uint8 b) {
    SDL_SetRenderDrawColor(renderer_, r, g, b, 0xFF);
}

Image Renderer::createTextImage(std::string text, const ColorRGB &rgb) const {
    SDL_Surface *surface = TTF_RenderText_Solid(
        font_, text.c_str(),
        {std::get<0>(rgb), std::get<1>(rgb), std::get<2>(rgb)});
    if (surface == nullptr) {
        SDLError::checkTTFError();
    }
    auto texture = SDL_CreateTextureFromSurface(renderer_, surface);
    if (texture == nullptr) {
        SDLError::checkSDLError();
    }
    auto image = Image(texture, surface->w, surface->h);
    SDL_FreeSurface(surface);
    return image;
}