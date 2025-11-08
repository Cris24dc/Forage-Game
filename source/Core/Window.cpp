#include "Core/Window.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Core {
    Window::Window(std::string title, int width, int height) {
        this->title = title;
        this->width = width;
        this->height = height;

        glfwInit();

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        this->window = glfwCreateWindow(this->width, this->height, this->title.c_str(), nullptr, nullptr);
        glfwMakeContextCurrent(this->window);

        gladLoadGL();
        glViewport(0, 0, this->width, this->height);
    }

    Window::~Window() {
        glfwDestroyWindow(this->window);
        glfwTerminate();
    }

    GLFWwindow* Window::getWindow() {
        return this->window;
    }

    bool Window::shouldClose() const {
        return glfwWindowShouldClose(this->window);
    }

    void Window::onUpdate() {
        glfwSwapBuffers(this->window);
        glfwPollEvents();
    };
}
