#include <Core/Game.h>
#include <ECS/Components.h>
#include <Graphics/Texture.h>
#include <Graphics/Window.h>
#include <Core/MapLoader.h>

namespace Core {
    Game::Game(std::string name, int width, int height) 
    : _window(std::make_unique<Graphics::Window>(name, width, height)),
      _registry(std::make_unique<ECS::Registry>()),
      _timer(std::make_unique<Timer>()),
      _renderSystem(std::make_unique<Systems::RenderSystem>()),
      _movementSystem(std::make_unique<Systems::MovementSystem>()),
      _animationSystem(std::make_unique<Systems::AnimationSystem>())
    {
        _renderSystem->Init(width, height);


        int tilePixelSize = 100;
        int sheetWidthInTiles = 12;
        int sheetHeightInTiles = 20;
        
        auto tileSheetTexture = std::make_shared<Graphics::Texture>("assets/textures/Tiles/Tileset.png");
        
        Core::MapLoader loader(
            tileSheetTexture, 
            sheetWidthInTiles, 
            sheetHeightInTiles, 
            tilePixelSize, 
            tilePixelSize
        );

        loader.LoadMap("assets/maps/lvl1.txt", *_registry);


        // auto houseTexture = std::make_shared<Graphics::Texture>("assets/textures/Objects/House.png");

        // Entity house = _registry->CreateEntity();

        // _registry->AddTransform(house, TransformComponent{
        //     .position = {600.0f, 180.0f},
        //     .scale = {300.0f, 500.0f}
        // });
        // _registry->AddSprite(house, SpriteComponent{
        //     .texture = houseTexture,
        //     .layer = 2
        // });


        auto idleTexture = std::make_shared<Graphics::Texture>("assets/textures/Player/Idle.png");
        auto walkTexture = std::make_shared<Graphics::Texture>("assets/textures/Player/Walk.png");

        Entity player = _registry->CreateEntity();

        SpriteAnimationComponent animComponent;

        animComponent.animations[AnimationState::Idle] = AnimationData{
            .textureSheet = idleTexture,
            .numCols = 4,
            .numRows = 3,
            .frameDuration = 0.2f
        };

        animComponent.animations[AnimationState::Walk] = AnimationData{
            .textureSheet = walkTexture,
            .numCols = 6,
            .numRows = 3,
            .frameDuration = 0.1f
        };
        
        _registry->AddTransform(player, TransformComponent{
            .position = {100.0f, 100.0f},
            .scale = {200.0f, 200.0f}
        });
        _registry->AddPlayerInput(player, PlayerInputComponent{});
        _registry->AddSprite(player, SpriteComponent{ 
            .texture = idleTexture,
            .layer = 1
        });
        _registry->AddAnimationState(player, AnimationStateComponent{});
        _registry->AddSpriteAnimation(player, animComponent);
    }

    Game::~Game() {}

    void Game::Run() {
        while (!_window->shouldClose()) {
            float dt = _timer->Tick();

            _movementSystem->Update(*_registry, dt, _window->getWindow());
            _animationSystem->Update(*_registry, dt);

            _window->clear();
            _renderSystem->Draw(*_registry);
            _window->onUpdate();
        }
    }
}