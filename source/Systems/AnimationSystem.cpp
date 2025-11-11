#include <Systems/AnimationSystem.h>
#include <ECS/Components.h>

namespace Systems {
    void AnimationSystem::Update(ECS::Registry& registry, float dt) {
        for (Entity e = 0; e < MAX_ENTITIES; e++) {
            if (registry.HasSprite(e) && registry.HasSpriteAnimation(e) && registry.HasAnimationState(e)) {
                
                auto& sprite = registry.GetSprite(e);
                auto& anim = registry.GetSpriteAnimation(e);
                auto& state = registry.GetAnimationState(e);

                AnimationData& currentAnimData = anim.animations.at(state.currentState);
                sprite.texture = currentAnimData.textureSheet;
                
                anim.elapsedTime += dt;
                if (anim.elapsedTime >= currentAnimData.frameDuration) {
                    anim.elapsedTime -= currentAnimData.frameDuration;
                    anim.currentFrame = (anim.currentFrame + 1) % currentAnimData.numCols;
                }
                
                sprite.flipX = false;

                int col = anim.currentFrame;
                int row = 0;

                switch (state.currentDirection) {
                    case ViewDirection::Down:
                        row = 2;
                        break;
                    case ViewDirection::Up:
                        row = 1;
                        break;
                    case ViewDirection::Right:
                        row = 0;
                        break;
                    case ViewDirection::Left:
                        row = 0;
                        sprite.flipX = true;
                        break;
                }

                sprite.uvScale.x = 1.0f / (float)currentAnimData.numCols;
                sprite.uvScale.y = 1.0f / (float)currentAnimData.numRows;

                sprite.uvOffset.x = (float)col * sprite.uvScale.x;
                sprite.uvOffset.y = (float)row * sprite.uvScale.y;
            }
        }
    }
}