#pragma once

#include <Core/Timer.h>
#include <Graphics/Window.h>
#include <ECS/Registry.h>
#include <Systems/RenderSystem.h>

#include <memory>
#include <string>

namespace Core {
    class Game {
    private:
        std::unique_ptr<Timer> _timer;
        std::unique_ptr<Graphics::Window> _window;
        std::unique_ptr<ECS::Registry> _registry;
        std::unique_ptr<Systems::RenderSystem> _renderSystem;

    public:
        Game(std::string name, int width, int height);
        ~Game();

        void Run();
    };
}
