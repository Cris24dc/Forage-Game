#pragma once

#include <ECS/Registry.h>

namespace Systems {
    class AnimationSystem {
    public:
        void Update(ECS::Registry& registry, float dt);
    };
}