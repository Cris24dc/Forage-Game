#include <Core/Window.h>

#include <memory>

namespace Core {
    class Game {
    private:
        Window win_obj;
        bool isRunning;
    public:
        Game();
        ~Game();

        void Run();
    };
}
