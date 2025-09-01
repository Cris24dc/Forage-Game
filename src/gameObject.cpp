#include "gameObject.hpp"

GameObject::GameObject(SDL_Renderer* renderer, int xPos, int yPos) {
    this->xPos = xPos;
    this->yPos = yPos;
    this->renderer = renderer;

    // Idle front
    idleFront.push_back(TextureManager::loadTexture("assets/player/player_front_standing_1.png", renderer));
    idleFront.push_back(TextureManager::loadTexture("assets/player/player_front_standing_2.png", renderer));

    // Idle back
    idleBack.push_back(TextureManager::loadTexture("assets/player/player_back_standing_1.png", renderer));
    idleBack.push_back(TextureManager::loadTexture("assets/player/player_back_standing_2.png", renderer));

    // Idle left
    idleLeft.push_back(TextureManager::loadTexture("assets/player/player_left_standing_1.png", renderer));
    idleLeft.push_back(TextureManager::loadTexture("assets/player/player_left_standing_2.png", renderer));

    // Idle right
    idleRight.push_back(TextureManager::loadTexture("assets/player/player_right_standing_1.png", renderer));
    idleRight.push_back(TextureManager::loadTexture("assets/player/player_right_standing_2.png", renderer));

    // Walking front
    walkFront.push_back(TextureManager::loadTexture("assets/player/player_front_walking_1.png", renderer));
    walkFront.push_back(TextureManager::loadTexture("assets/player/player_front_walking_2.png", renderer));

    currentTexture = idleFront[0];
    currentIdleIndex = 0;
    currentWalkIndex = 0;
    lastFrameTime = SDL_GetTicks();
    isMoving = false;
    facing = Direction::FRONT;

    destRect = {xPos, yPos, 128, 128};
}

GameObject::~GameObject() {
    for (auto tex : idleFront) SDL_DestroyTexture(tex);
    for (auto tex : idleBack) SDL_DestroyTexture(tex);
    for (auto tex : idleLeft) SDL_DestroyTexture(tex);
    for (auto tex : idleRight) SDL_DestroyTexture(tex);
    for (auto tex : walkFront) SDL_DestroyTexture(tex);
}

void GameObject::handleInput(const Uint8* keystate) {
    isMoving = false;

    if (keystate[SDL_SCANCODE_W]) { 
        yPos -= 2; 
        facing = Direction::BACK;
        isMoving = true;
    }
    if (keystate[SDL_SCANCODE_S]) { 
        yPos += 2; 
        facing = Direction::FRONT;
        isMoving = true;
    }
    if (keystate[SDL_SCANCODE_A]) { 
        xPos -= 2; 
        facing = Direction::LEFT;
        isMoving = true;
    }
    if (keystate[SDL_SCANCODE_D]) { 
        xPos += 2; 
        facing = Direction::RIGHT;
        isMoving = true;
    }
}

void GameObject::update() {
    Uint32 now = SDL_GetTicks();

    if (isMoving) {
        if (facing == Direction::FRONT) {
            // animăm mersul (2 frame-uri)
            if (now - lastFrameTime > 300) {
                currentWalkIndex = (currentWalkIndex + 1) % walkFront.size();
                lastFrameTime = now;
            }
            currentTexture = walkFront[currentWalkIndex];
        } else {
            // pentru restul direcțiilor -> doar standing_1
            switch (facing) {
                case Direction::BACK:  currentTexture = idleBack[0]; break;
                case Direction::LEFT:  currentTexture = idleLeft[0]; break;
                case Direction::RIGHT: currentTexture = idleRight[0]; break;
                default: break;
            }
        }
    } else {
        // idle animation (2 frame-uri)
        if (now - lastFrameTime > 450) {
            currentIdleIndex = (currentIdleIndex + 1) % 2;
            lastFrameTime = now;
        }

        switch (facing) {
            case Direction::FRONT:  currentTexture = idleFront[currentIdleIndex]; break;
            case Direction::BACK:   currentTexture = idleBack[currentIdleIndex]; break;
            case Direction::LEFT:   currentTexture = idleLeft[currentIdleIndex]; break;
            case Direction::RIGHT:  currentTexture = idleRight[currentIdleIndex]; break;
        }
    }

    destRect.x = xPos;
    destRect.y = yPos;
}

void GameObject::render() {
    SDL_RenderCopy(renderer, currentTexture, NULL, &destRect);
}
