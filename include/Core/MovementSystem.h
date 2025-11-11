#pragma once

#include <Core/Registry.h>

#include <GLFW/glfw3.h>

namespace Core {
    class MovementSystem {
    public:
        void Update(Registry& registry, float dt, GLFWwindow* window);
    };
}