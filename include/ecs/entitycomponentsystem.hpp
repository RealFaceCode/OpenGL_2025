#pragma once

#include "componentmanager.hpp"
#include "systemmanager.hpp"
#include "entityidgenerator.hpp"
#include "entitycreatesystemmanager.hpp"

class EntityComponentSystem
{
public:
    EntityComponentSystem()
    : cm(), sm(cm), ecsm(cm, idGen)
    {}

    template<class System>
    requires std::derived_from<System, ISystem>
    void addSystem()
    {
        sm.addSystem<System>();
    }

    template<class SystemType>
    requires std::derived_from<SystemType, ISystem>
    void addSystem(const SystemType& system)
    {
        sm.addSystem<SystemType>(system);
    }

    template<class SystemType>
    requires std::derived_from<SystemType, IEntityCreateSystem>
    void addCreateSystem()
    {
        ecsm.addSystem<SystemType>();
    }

    template<class SystemType>
    requires std::derived_from<SystemType, IEntityCreateSystem>
    void addCreateSystem(const SystemType& createSystem)
    {
        ecsm.addSystem<SystemType>(createSystem);
    }

    template<class SystemType>
    requires std::derived_from<SystemType, IEntityCreateSystem>
    void removeCreateSystem(EntityID id)
    {
        ecsm.remove<SystemType>();
    }

    template<class SystemType, class ... Args>
    requires std::derived_from<SystemType, IEntityCreateSystem> && std::is_invocable_v<decltype(&SystemType::create), SystemType*, ComponentManager&, EntityID, Args...>
    EntityID createEntity(Args&&... args)
    {
        return ecsm.createEntity<SystemType>(std::forward<Args>(args)...);
    }

    void removeEntity(EntityID id)
    {
        cm.removeEntity(id);
        idGen.destroy(id);
    }

    template<class SystemType>
    requires std::derived_from<SystemType, ISystem>
    void updateSystem(float deltaTime)
    {
        sm.update<SystemType>(deltaTime);
    }

    void updateAllSystems(float deltaTime)
    {
        sm.updateAll(deltaTime);
    }

private:
    ComponentManager cm;
    SystemManager sm;
    EntityIDGenerator idGen;
    EntityCreateSystemManager ecsm;
};