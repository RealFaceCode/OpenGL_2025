#pragma once

#include <unordered_map>
#include <typeindex>
#include <generator>

#include "defines.hpp"
#include "componentstorage.hpp"

class ComponentManager
{
public:
    template<class Component>
    ComponentStorage<Component>& getStorage()
    {
        auto [it, success] = storage.try_emplace(std::type_index(typeid(Component)), std::make_unique<ComponentStorage<Component>>());
        return *static_cast<ComponentStorage<Component>*>(it->second.get());
    }

    template<class Component>
    void addComponent(EntityID id, const Component&& component)
    {
        auto& storage = getStorage<Component>();
        storage.add(id, std::move(component));
        entityToStorages[id].emplace_back(&storage);
    }

    template<class Component>
    void removeComponent(EntityID id)
    {
        getStorage<Component>().remove(id);
    }

    void removeEntity(EntityID id)
    {
        auto it = entityToStorages.find(id);
        if(it == entityToStorages.end())
            return;

        for(auto* storage : it->second)
            storage->remove(id);

        entityToStorages.erase(it);
    }

    template<class Component>
    Component* getComponent(EntityID id)
    {
        return getStorage<Component>().get(id);
    }

private:
    std::unordered_map<std::type_index, std::unique_ptr<IComponentStorage>> storage;
    std::unordered_map<EntityID, std::vector<IComponentStorage*>> entityToStorages;

};

template<class ... Components>
std::generator<std::tuple<Components&...>> LazyView(ComponentManager& cm)
{
    using FirstComponent = std::tuple_element_t<0, std::tuple<Components...>>;
    auto storages = std::tuple<ComponentStorage<Components>&...>(cm.getStorage<Components>()...);
    auto& firstStorage = std::get<0>(storages);

    for (size_t i = 0; i < firstStorage.size(); ++i)
    {
        EntityID e = firstStorage.entitiesAt(i);
        if ((std::get<ComponentStorage<Components>&>(storages).has(e) && ...))
        {
            co_yield std::tie(*std::get<ComponentStorage<Components>&>(storages).get(e)...);
        }
    }
}

template<class ... Components>
std::generator<std::tuple<EntityID, Components&...>> LazyViewWithEntity(ComponentManager& cm)
{
    using FirstComponent = std::tuple_element_t<0, std::tuple<Components...>>;
    auto storages = std::tuple<ComponentStorage<Components>&...>(cm.getStorage<Components>()...);
    auto& firstStorage = std::get<0>(storages);

    for (size_t i = 0; i < firstStorage.size(); ++i)
    {
        EntityID e = firstStorage.entitiesAt(i);
        if ((std::get<ComponentStorage<Components>&>(storages).has(e) && ...))
        {
            co_yield std::tuple_cat(std::tuple{ e }, std::tie(*std::get<ComponentStorage<Components>&>(storages).get(e)...));
        }
    }
}
