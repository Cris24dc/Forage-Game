#include <Core/MovementSystem.h>
#include <Core/Components.h>

namespace Core {
    void MovementSystem::Update(Registry& registry, float dt, GLFWwindow* window) {
        for (Entity e = 0; e < MAX_ENTITIES; e++) {
            if (registry.HasPlayerInput(e) && registry.HasTransform(e) && registry.HasAnimationState(e)) {
                
                auto& transform = registry.GetTransform(e);
                auto& input = registry.GetPlayerInput(e);
                auto& animState = registry.GetAnimationState(e);

                bool isMoving = false;
                AnimationState oldState = animState.currentState;
                ViewDirection oldDirection = animState.currentDirection;

                animState.currentState = AnimationState::Idle;

                if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
                    transform.position.y += input.speed * dt;
                    animState.currentState = AnimationState::Walk;
                    animState.currentDirection = ViewDirection::Up;
                    isMoving = true;
                }
                if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
                    transform.position.y -= input.speed * dt;
                    animState.currentState = AnimationState::Walk;
                    animState.currentDirection = ViewDirection::Down;
                    isMoving = true;
                }
                if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
                    transform.position.x -= input.speed * dt;
                    animState.currentState = AnimationState::Walk;
                    animState.currentDirection = ViewDirection::Left;
                    isMoving = true;
                }
                if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
                    transform.position.x += input.speed * dt;
                    animState.currentState = AnimationState::Walk;
                    animState.currentDirection = ViewDirection::Right;
                    isMoving = true;
                }
                if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
                    transform.rotation += input.speed * dt;
                }


                if (oldState != animState.currentState || oldDirection != animState.currentDirection) {
                    animState.stateChanged = true;
                }
            }
        }
    }
}