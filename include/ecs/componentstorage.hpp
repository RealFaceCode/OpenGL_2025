#pragma once

#include <unordered_map>
#include <vector>

#include "defines.hpp"

class IComponentStorage
{
public:
    virtual ~IComponentStorage() = default;

    virtual void remove(EntityID id) = 0;
    virtual bool has(EntityID id) const = 0;
    virtual size_t size() const = 0;
};

template<class Component>
class ComponentStorage : public IComponentStorage
{
public:
    void remove(EntityID id) override
    {
        auto it = entityComponentsMap.find(id);
        if(it == entityComponentsMap.end())
            return;

        size_t index = it->second;
        size_t lastIndex = components.size() - 1;

        components[index] = std::move(components[lastIndex]);
        entities[index] = entities[lastIndex];

        entityComponentsMap[entities[index]] = index;

        components.pop_back();
        entities.pop_back();
        entityComponentsMap.erase(it);
    }

    bool has(EntityID id) const override
    {
        return entityComponentsMap.contains(id);
    }

    size_t size() const override
    {
        return components.size();
    }

    Component* get(EntityID id)
    {
        auto it = entityComponentsMap.find(id);
        if(it == entityComponentsMap.end())
            return nullptr;
        
        return &components[it->second];
    }

    void add(EntityID id, const Component&& component)
    {
        auto [it, success] = entityComponentsMap.try_emplace(id, components.size());
        if(!success)
            return;

        components.emplace_back(std::move(component));
        entities.emplace_back(id);
    }

    EntityID entitiesAt(size_t index) const
    {
        return entities.at(index);
    }

private:
    std::vector<Component> components;
    std::vector<EntityID> entities;
    std::unordered_map<EntityID, size_t> entityComponentsMap;
};