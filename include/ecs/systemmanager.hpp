#pragma once

#include <unordered_map>
#include <typeindex>

#include "ecs/componentmanager.hpp"
#include "system.hpp"

class SystemManager
{
public:
    explicit SystemManager();

    SystemManager(ComponentManager& componentManager)
    : cm(componentManager)
    {}

    ~SystemManager() = default;

    template<class SystemType>
    requires std::derived_from<SystemType, ISystem>
    void addSystem()
    {
        auto [it, success] = systems.try_emplace(std::type_index(typeid(SystemType)), std::make_shared<SystemType>());
    }

    template<class SystemType>
    requires std::derived_from<SystemType, ISystem>
    void addSystem(const SystemType& system)
    {
        auto [it, success] = systems.try_emplace(std::type_index(typeid(SystemType)), std::make_shared<SystemType>(system));
    }

    template<class SystemType>
    requires std::derived_from<SystemType, ISystem>
    void remove()
    {
        systems.erase(std::type_index(typeid(SystemType)));
    }

    template<class SystemType>
    requires std::derived_from<SystemType, ISystem>
    void update(float deltaTime)
    {
        systems.at(std::type_index(typeid(SystemType)))->update(cm, deltaTime);
    }

    void updateAll(float deltaTime)
    {
        for(auto& system : systems)
            system.second->update(cm, deltaTime);
    }

private: 
    std::unordered_map<std::type_index, std::shared_ptr<ISystem>> systems;
    ComponentManager& cm;
};