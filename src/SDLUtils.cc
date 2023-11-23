#include <string>
#include "SDLUtils.h"

void SDLError::checkSDLError() {
    std::string message = SDL_GetError();
    if (!message.empty()) {
        throw SDLException();
    }
}
