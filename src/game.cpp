#include "game.hpp"

SDL_Rect dest = {100, 100, 128, 128};
SDL_Texture* texture1;
SDL_Texture* texture2;
SDL_Texture* currentTexture;
int cnt = 0;

Game::Game() {
    this->running = false;
    this->window = nullptr;
    this->renderer = nullptr;
}

Game::~Game() {
    logMessage(LogLevel::INFO, "SDL Cleaned");
    if (this->renderer) {
        SDL_DestroyRenderer(this->renderer);
        this->renderer = nullptr;
    }
    if (this->window) {
        SDL_DestroyWindow(this->window);
        this->window = nullptr;
    }
    SDL_Quit();
}

bool Game::init(const char* title, bool fullscreen) {
    unsigned int flags = fullscreen ? SDL_WINDOW_FULLSCREEN : SDL_WINDOW_MAXIMIZED;

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        logMessage(LogLevel::ERROR, "SDL failed to initialize");
        return false;
    }
    logMessage(LogLevel::INFO, "SDL initialized");

    this->window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, flags);

    if(!this->window) {
        logMessage(LogLevel::ERROR, "Window creation failed");
        return false;
    }
    logMessage(LogLevel::INFO, "Window created");

    this->renderer = SDL_CreateRenderer(this->window, -1, 0);

    if(!this->renderer) {
        logMessage(LogLevel::ERROR, "Renderer creation failed");
        return false;
    }
    logMessage(LogLevel::INFO, "Renderer created");

    texture1 = TextureManager::loadTexture("assets/player/player_front_standing_1.png", this->renderer);
    texture2 = TextureManager::loadTexture("assets/player/player_front_standing_2.png", this->renderer);

    this->running = true;
    return true;
}

bool Game::isRunning() const {
    return this->running;
}

void Game::handleEvent() {
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) this->running = false;
    }
}

void Game::update() {
    cnt++;
    if (cnt % 2 == 0) {
        currentTexture = texture1;
        SDL_Delay(300);
    }
    else {
        currentTexture = texture2;
        SDL_Delay(450);
    }
}

void Game::render() {
    SDL_SetRenderDrawColor(this->renderer, 140, 105, 232, 0);
    SDL_RenderClear(this->renderer);
    SDL_RenderCopy(this->renderer, currentTexture, NULL, &dest);
    SDL_RenderPresent(this->renderer);
}
