#pragma once
#include <cassert>
#include <unordered_map>
#include <vector>

#include "Entities/Entity.h"

template <typename T>
class ComponentPool
{
public:
    std::vector<T> components;
    std::vector<EntityId> entities;
    std::unordered_map<EntityId, size_t> entityToIndex;

    void Add(const EntityId id, const T& component)
    {
        assert(entityToIndex.find(id) == entityToIndex.end() && "Entity already exists!");

        const size_t index = components.size();
        components.push_back(component);
        entities.push_back(id);
        entityToIndex[id] = index;
    }

    T* Get(const EntityId id)
    {
        const auto it = entityToIndex.find(id);
        if (it != entityToIndex.end())
        {
            return &components[it->second];
        }
        return nullptr;
    }

    void Remove(const EntityId id)
    {
        const auto it = entityToIndex.find(id);
        if (it == entityToIndex.end()) return;

        size_t index = it->second;
        size_t last = components.size() - 1;

        std::swap(components[index], components[last]);
        std::swap(entities[index], entities[last]);

        entityToIndex[entities[index]] = index;
        components.pop_back();
        entities.pop_back();
        entityToIndex.erase(it);
    }

    size_t Size() const { return components.size(); }

    EntityId GetEntity(const size_t i) const { return entities[i]; }

    T& GetByIndex(size_t i) { return components[i]; }
};
