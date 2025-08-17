#include "game.hpp"

Game::Game() {
    this->running = false;
    this->window = nullptr;
    this->renderer = nullptr;
}

Game::~Game() {
    logMessage(LogLevel::INFO, "SDL Cleaned");
    if (renderer) {
        SDL_DestroyRenderer(renderer);
        renderer = nullptr;
    }
    if (window) {
        SDL_DestroyWindow(window);
        window = nullptr;
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
    // update
}

void Game::render() {
    SDL_SetRenderDrawColor(this->renderer, 140, 105, 232, 0);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
}
