#pragma once

#include <ECS/Registry.h>

#include <GLFW/glfw3.h>

namespace Systems {
    class MovementSystem {
    public:
        void Update(ECS::Registry& registry, float dt, GLFWwindow* window);
    };
}