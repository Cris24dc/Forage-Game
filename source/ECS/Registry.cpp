#include <ECS/Registry.h>

namespace ECS {
    Registry::Registry() {
        for (Entity e = 0; e < MaxEntities; e++) {
            _availableEntities.push(e);
        }
    }

    Entity Registry::CreateEntity() {
        Entity e = _availableEntities.front();
        _availableEntities.pop();
        _livingEntityCount++;
        return e;
    }

    void Registry::DestroyEntity(Entity entity) {
        _availableEntities.push(entity);
        _livingEntityCount--;

        for (auto const& [type, array] : _componentArrays) {
            array->EntityDestroyed(entity);
        }
    }
}
