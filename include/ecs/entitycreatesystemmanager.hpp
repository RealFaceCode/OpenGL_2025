#pragma once

#include <unordered_map>
#include <typeindex>

#include "ecs/componentmanager.hpp"
#include "ecs/entitycreatesystem.hpp"
#include "ecs/entityidgenerator.hpp"

class EntityCreateSystemManager
{
public:
    EntityCreateSystemManager(ComponentManager& componentManager, EntityIDGenerator& entityIDGenerator)
    : cm(componentManager), idGen(entityIDGenerator)
    {}

    template<class SystemType>
    requires std::derived_from<SystemType, IEntityCreateSystem>
    void addSystem()
    {
        auto [it, success] = systems.try_emplace(std::type_index(typeid(SystemType)), std::make_shared<SystemType>());
    }

    template<class SystemType>
    requires std::derived_from<SystemType, IEntityCreateSystem>
    void addSystem(const SystemType& system)
    {
        auto [it, success] = systems.try_emplace(std::type_index(typeid(SystemType)), std::make_shared<SystemType>(system));
    }

    template<class SystemType>
    requires std::derived_from<SystemType, IEntityCreateSystem>
    void remove()
    {
        systems.erase(std::type_index(typeid(SystemType)));
    }

    template<typename SystemType, typename... Args>
    requires std::derived_from<SystemType, IEntityCreateSystem> && std::is_invocable_v<decltype(&SystemType::create), SystemType*, ComponentManager&, EntityID, Args...>
    EntityID createEntity(Args&&... args)
    {
        auto id = idGen.create();
        auto system_ptr = systems.at(std::type_index(typeid(SystemType))).get();
        static_cast<SystemType*>(system_ptr)->create(cm, id, std::forward<Args>(args)...);
        return id;
    }

private:
    ComponentManager& cm;
    EntityIDGenerator& idGen;
    std::unordered_map<std::type_index, std::shared_ptr<IEntityCreateSystem>> systems;
};