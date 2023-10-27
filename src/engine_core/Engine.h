#include <SDL2/SDL.h>
#include <memory>
#include <string>

constexpr int WINDOW_WIDTH = 1600;
constexpr int WINDOW_HEIGHT = 900;

class Engine {

    SDL_Window *window_;
    SDL_Renderer *renderer_;
    SDL_Surface *surface_;
    SDL_Texture *texture_;

    SDL_Texture *loadTexture(std::string path) const;
    public:
    Engine();
    ~Engine();
    Engine(const Engine &rhs) = delete;
    Engine &operator=(const Engine &rhx) = delete;
    
    void startLoop();
};