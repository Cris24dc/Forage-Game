#pragma once

#include <Core/Window.h>
#include <Core/Registry.h>
#include <Core/Timer.h>
#include <Core/RenderSystem.h>
#include <Core/MovementSystem.h>
#include <Core/AnimationSystem.h>

namespace Core {
    class Game {
    private:
        std::unique_ptr<Window> _window;
        std::unique_ptr<Registry> _registry;
        std::unique_ptr<Timer> _timer;
        std::unique_ptr<RenderSystem> _renderSystem;
        std::unique_ptr<MovementSystem> _movementSystem;
        std::unique_ptr<AnimationSystem> _animationSystem;

    public:
        Game(std::string name, int width, int height);
        ~Game();

        void Run();
    };
}
