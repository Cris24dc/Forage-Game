#pragma once

#include <string>

struct GLFWwindow;

namespace Core {
    class Window {
    private:
        std::string _title;
        int _width;
        int _height;
        GLFWwindow* _window = nullptr;
        
    public:
        Window(std::string name, int width, int height);
        ~Window();
 
        GLFWwindow* getWindow() const;
        bool shouldClose() const;
        void clear();
        void onUpdate();
    };
}
