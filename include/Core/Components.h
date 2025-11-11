#pragma once

#include <Core/Texture.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <memory>
#include <map>

enum class AnimationState {
    Idle,
    Walk
};

enum class ViewDirection {
    Down = 0,
    Up = 1,
    Left = 2,
    Right = 3
};

struct TransformComponent {
    glm::vec2 position{0.0f, 0.0f};
    glm::vec2 scale{1.0f, 1.0f};
    float rotation{0.0f};
};

struct SpriteComponent {
    std::shared_ptr<Core::Texture> texture = nullptr;
    glm::vec4 color{1.0f, 1.0f, 1.0f, 1.0f};
    glm::vec2 uvOffset{0.0f, 0.0f};
    glm::vec2 uvScale{1.0f, 1.0f};

    int layer = 0;
    bool flipX = false;
};

struct PlayerInputComponent {
    float speed = 200.0f;
};

struct AnimationStateComponent {
    AnimationState currentState = AnimationState::Idle;
    ViewDirection currentDirection = ViewDirection::Down;
    
    bool stateChanged = true;
};

struct AnimationData {
    std::shared_ptr<Core::Texture> textureSheet;
    int numCols;
    int numRows;
    float frameDuration;
};

struct SpriteAnimationComponent {
    std::map<AnimationState, AnimationData> animations;
    
    float elapsedTime = 0.0f;
    int currentFrame = 0;
};
