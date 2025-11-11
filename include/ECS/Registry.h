#pragma once

#include <ECS/Components.h>

#include <cstdint>
#include <array>
#include <queue>
#include <stdexcept>
#include <memory>

using Entity = std::uint32_t;
constexpr std::size_t MAX_ENTITIES = 100;

namespace ECS {
    class Registry {
    private:
        std::queue<Entity> _AvailableEntities;
        uint32_t _LivingEntityCount = 0;

        std::array<std::unique_ptr<TransformComponent>, MAX_ENTITIES> _Transforms;
        std::array<std::unique_ptr<SpriteComponent>, MAX_ENTITIES> _Sprites;
        std::array<std::unique_ptr<PlayerInputComponent>, MAX_ENTITIES> _PlayerInputs;
        std::array<std::unique_ptr<SpriteAnimationComponent>, MAX_ENTITIES> _SpriteAnimations;
        std::array<std::unique_ptr<AnimationStateComponent>, MAX_ENTITIES> _AnimationStates;

    public:
        Registry() {
            for (Entity e = 0; e < static_cast<Entity>(MAX_ENTITIES); e++) {
                _AvailableEntities.push(e);
            }
        }

        Entity CreateEntity() {
            if (_LivingEntityCount >= static_cast<uint32_t>(MAX_ENTITIES)) {
                throw std::runtime_error("Too many entities");
            }
            
            Entity id = _AvailableEntities.front();
            _AvailableEntities.pop();
            _LivingEntityCount++; 
            return id;
        }

        void DestroyEntity(Entity entity) {
            _Transforms[entity].reset();
            _Sprites[entity].reset();
            _PlayerInputs[entity].reset();
            _SpriteAnimations[entity].reset();
            _AnimationStates[entity].reset();
            
            _AvailableEntities.push(entity);
            _LivingEntityCount--;
        }


        void AddTransform(Entity e, TransformComponent comp) {
             _Transforms[e] = std::unique_ptr<TransformComponent>(new TransformComponent(comp)); 
        }
        TransformComponent& GetTransform(Entity e) { 
            return *_Transforms[e]; 
        }
        bool HasTransform(Entity e) { 
            return _Transforms[e] != nullptr; 
        }


        void AddSprite(Entity e, SpriteComponent comp) { 
            _Sprites[e] = std::unique_ptr<SpriteComponent>(new SpriteComponent(comp)); 
        }
        SpriteComponent& GetSprite(Entity e) { 
            return *_Sprites[e]; 
        }
        bool HasSprite(Entity e) { 
            return _Sprites[e] != nullptr; 
        }


        void AddPlayerInput(Entity e, PlayerInputComponent comp) { 
            _PlayerInputs[e] = std::unique_ptr<PlayerInputComponent>(new PlayerInputComponent(comp)); 
        }
        PlayerInputComponent& GetPlayerInput(Entity e) { 
            return *_PlayerInputs[e]; 
        }
        bool HasPlayerInput(Entity e) { 
            return _PlayerInputs[e] != nullptr; 
        }


        void AddSpriteAnimation(Entity e, SpriteAnimationComponent comp) { 
            _SpriteAnimations[e] = std::unique_ptr<SpriteAnimationComponent>(new SpriteAnimationComponent(comp)); 
        }
        SpriteAnimationComponent& GetSpriteAnimation(Entity e) { 
            return *_SpriteAnimations[e]; 
        }
        bool HasSpriteAnimation(Entity e) { 
            return _SpriteAnimations[e] != nullptr; 
        }
        

        void AddAnimationState(Entity e, AnimationStateComponent comp) { 
            _AnimationStates[e] = std::unique_ptr<AnimationStateComponent>(new AnimationStateComponent(comp)); 
        }
        AnimationStateComponent& GetAnimationState(Entity e) { 
            return *_AnimationStates[e]; 
        }
        bool HasAnimationState(Entity e) { 
            return _AnimationStates[e] != nullptr; 
        }
    };
}