#ifndef TEXTUREMANAGER_HPP
#define TEXTUREMANAGER_HPP

#include "game.hpp"
#include <SDL2/SDL_image.h>

class TextureManager {
private:
    TextureManager();

public:
    static SDL_Texture* loadTexture(const char* file, SDL_Renderer* renderer);

};

#endif