#include <Core/Game.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Core {
    Game::Game() : win_obj("My game", 800, 800) {
        this->isRunning = false;
    }

    Game::~Game() {
        glfwTerminate();
    }

    void Game::Run() {
        while(!this->win_obj.shouldClose()) {
            glClearColor(1.0f, 0.95f, 0.76f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            this->win_obj.onUpdate();
        }
    }
}
