#include <Graphics/Window.h>

#include <vendor/glad/glad.h>
#include <GLFW/glfw3.h>

namespace Graphics {
    Window::Window(std::string title, int width, int height) {
        _title = title;
        _width = width;
        _height = height;

        glfwInit();

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        _window = glfwCreateWindow(_width, _height, _title.c_str(), nullptr, nullptr);
        glfwMakeContextCurrent(_window);

        gladLoadGL();
        glViewport(0, 0, _width, _height);
    }

    Window::~Window() {
        glfwDestroyWindow(_window);
        glfwTerminate();
    }

    GLFWwindow* Window::getWindow() const{
        return _window;
    }

    bool Window::shouldClose() const {
        return glfwWindowShouldClose(_window);
    }

    void Window::clear() {
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void Window::onUpdate() {
        glfwSwapBuffers(_window);
        glfwPollEvents();
    };
}
