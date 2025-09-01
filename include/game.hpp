#ifndef GAME_HPP
#define GAME_HPP

#include "logger.hpp"
#include "textureManager.hpp"
#include <SDL2/SDL.h>
#include <vector>
#include <iostream>

class GameObject;

class Game {
private:
    bool running;
    SDL_Window* window;
    SDL_Renderer* renderer;
    std::vector<GameObject*> objects;

public:
    Game();
    ~Game();

    bool init(const char* title, bool fullscreen);
    bool isRunning() const;
    void handleEvent();
    void render();
    void update();
};

#endif