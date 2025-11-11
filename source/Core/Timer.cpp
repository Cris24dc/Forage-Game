#include <Core/Timer.h>

#include <GLFW/glfw3.h>

namespace Core {
    Timer::Timer() {
        _lastFrameTime = (float)glfwGetTime();
    }

    float Timer::Tick() {
        float currentTime = (float)glfwGetTime();
        float deltaTime = currentTime - _lastFrameTime;
        _lastFrameTime = currentTime;

        return deltaTime;
    }
}