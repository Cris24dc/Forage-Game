#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include <SDL2/SDL.h>
#include <vector>
#include <string>
#include "textureManager.hpp"

enum class Direction {
    FRONT,
    BACK,
    LEFT,
    RIGHT
};

class GameObject {
public:
    GameObject(SDL_Renderer* renderer, int xPos, int yPos);
    ~GameObject();

    void handleInput(const Uint8* keystate);
    void update();
    void render();

private:
    int xPos, yPos;
    SDL_Renderer* renderer;

    // idle frames pentru fiecare direcție
    std::vector<SDL_Texture*> idleFront;
    std::vector<SDL_Texture*> idleBack;
    std::vector<SDL_Texture*> idleLeft;
    std::vector<SDL_Texture*> idleRight;

    // walking doar pentru front
    std::vector<SDL_Texture*> walkFront;

    SDL_Texture* currentTexture;

    int currentIdleIndex;
    int currentWalkIndex;
    Uint32 lastFrameTime;
    bool isMoving;
    Direction facing;

    SDL_Rect srcRect, destRect;
};

#endif
