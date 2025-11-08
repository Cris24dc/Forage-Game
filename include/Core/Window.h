#include <string>

struct GLFWwindow;

namespace Core {
    class Window {
    private:
        std::string title;
        int width;
        int height;
        GLFWwindow* window = nullptr;
    public:
        Window(std::string name, int width, int height);
        ~Window();

        GLFWwindow* getWindow();
        bool shouldClose() const;
        void onUpdate();
    };
}
