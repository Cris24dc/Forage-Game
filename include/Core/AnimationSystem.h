#pragma once

#include <Core/Registry.h>

namespace Core {
    class AnimationSystem {
    public:
        void Update(Registry& registry, float dt);
    };
}