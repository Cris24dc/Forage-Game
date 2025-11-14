#pragma once

#include <ECS/IComponentArray.h>

#include <array>
#include <bitset>
#include <memory>

namespace ECS {
    template <typename T>
    class ComponentArray : public IComponentArray {
    private:
        std::array<T, MaxEntities> _componentArray;
        std::bitset<MaxEntities> _hasComponentMask;
        
    public:
        ComponentArray() = default;
        ~ComponentArray() = default;

        void add(Entity entity, T component) {
            _componentArray[entity] = component;
            _hasComponentMask[entity] = 1;
        }

        void remove(Entity entity) {
            _hasComponentMask[entity] = 0;
        }

        T& get(Entity entity) {
            return _componentArray[entity];
        }

        bool has(Entity entity) {
            return _hasComponentMask[entity];
        }

        void EntityDestroyed(Entity entity) {
            if (_hasComponentMask[entity]) {
                remove(entity);
            }
        }
    };
}
