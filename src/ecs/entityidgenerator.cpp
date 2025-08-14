#include "ecs/entityidgenerator.hpp"

EntityID EntityIDGenerator::create()
{
    if (!freeList.empty())
    {
        uint32_t index = freeList.back();
        freeList.pop_back();
        return makeEntity(index, generations[index - 1]);
    }

    uint32_t index = static_cast<uint32_t>(generations.size() + 1);
    generations.emplace_back(1);
    return makeEntity(index, 1);
}

void EntityIDGenerator::destroy(EntityID entity)
{
    uint32_t index = getEntityIndex(entity);
    ++generations[index - 1];
    freeList.emplace_back(index);
}

bool EntityIDGenerator::isAlive(EntityID entity) const
{
    uint32_t index = getEntityIndex(entity);
    uint32_t gen = getEntityGeneration(entity);
    return index < generations.size() && generations[index - 1] == gen;
}
