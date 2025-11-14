#include <Core/Game.h>
#include <Components/Components.h>
#include <Graphics/Texture.h>
#include <Graphics/Window.h>
#include <ECS/Entity.h>

namespace Core {
    Game::Game(std::string name, int width, int height) 
    : _window(std::make_unique<Graphics::Window>(name, width, height)),
      _renderSystem(std::make_unique<Systems::RenderSystem>(width, height)),
      _timer(std::make_unique<Timer>()),
      _registry(std::make_unique<ECS::Registry>())
    {
        _registry->registerComponent<Components::Transform>();
        _registry->registerComponent<Components::Sprite>();

        auto idleTexture = std::make_shared<Graphics::Texture>("assets/textures/Player/Idle.png");
        auto walkTexture = std::make_shared<Graphics::Texture>("assets/textures/Player/Walk.png");
        
        ECS::Entity player = _registry->CreateEntity();
        
        _registry->addComponent<Components::Transform>(player, Components::Transform{
            .position = {100.0f, 100.0f},
            .scale = {200.0f, 200.0f}
        });
        _registry->addComponent<Components::Sprite>(player, Components::Sprite{ 
            .texture = idleTexture,
            .rows = 3,
            .columns = 4
        });

        auto& sprite = _registry->getComponent<Components::Sprite>(player);
        sprite.setSpriteSheetCell(0, 2);
    }

    Game::~Game() {}

    void Game::Run() {
        while (!_window->shouldClose()) {
            float dt = _timer->Tick();

            // system updates

            _window->clear();
            
            _renderSystem->draw(*_registry);

            _window->onUpdate();
        }
    }
}