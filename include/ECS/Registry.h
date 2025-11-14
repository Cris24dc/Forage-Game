#pragma once

#include <ECS/Entity.h>
#include <ECS/ComponentArray.h>

#include <cstdint>
#include <typeindex>
#include <memory>
#include <unordered_map>
#include <queue>

namespace ECS {
    class Registry {
    private:
        std::queue<Entity> _availableEntities;
        uint32_t _livingEntityCount{0};
        std::unordered_map<std::type_index, std::unique_ptr<IComponentArray>> _componentArrays;

        template <typename T>
        ComponentArray<T>& getComponentArray() {
            std::type_index typeIndex = typeid(T);
            auto it = _componentArrays.find(typeIndex);
            IComponentArray* basePtr = it->second.get();
            return *static_cast<ComponentArray<T>*>(basePtr);
        }
        
    public:
        Registry();
        ~Registry() = default;

        Entity CreateEntity();
        void DestroyEntity(Entity entity);

        template <typename T>
        void registerComponent() {
            std::type_index typeIndex = typeid(T);
            _componentArrays[typeIndex] = std::make_unique<ComponentArray<T>>();
        }

        template <typename T>
        void addComponent(Entity entity, T component) {
            getComponentArray<T>().add(entity, component);
        }

        template <typename T>
        void removeComponent(Entity entity) {
            getComponentArray<T>().remove(entity);
        }

        template <typename T>
        T& getComponent(Entity entity) {
            return getComponentArray<T>().get(entity);
        }

        template <typename T>
        bool hasComponent(Entity entity) {
            return getComponentArray<T>().has(entity);
        }
    };
}
