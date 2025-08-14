#pragma once

class ComponentManager;

class ISystem
{
public:
    virtual ~ISystem() = default;
    virtual void update(ComponentManager& cm, float deltaTime) = 0;
};