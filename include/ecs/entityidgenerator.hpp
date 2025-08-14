#pragma once

#include <vector>

#include "defines.hpp"

constexpr uint64_t ENTITY_INDEX_MASK = 0xFFFFFFFF00000000ull;
constexpr uint64_t ENTITY_GENERATION_MASK = 0x00000000FFFFFFFFull;
constexpr uint32_t ENTITY_INDEX_SHIFT = 32;
constexpr uint32_t ENTITY_GENERATION_SHIFT = 0;

constexpr uint64_t makeEntity(uint32_t index, uint32_t generation)
{
    return (static_cast<uint64_t>(index) << ENTITY_INDEX_SHIFT) | (static_cast<uint64_t>(generation) & ENTITY_GENERATION_MASK);
}

constexpr uint32_t getEntityIndex(EntityID e)
{
    return static_cast<uint32_t>((e >> ENTITY_INDEX_SHIFT) & 0xFFFFFFFFu);
}

constexpr uint32_t getEntityGeneration(EntityID e)
{
    return static_cast<uint32_t>(e & 0xFFFFFFFFu);
}

class EntityIDGenerator
{
public:
    EntityIDGenerator() = default;
    ~EntityIDGenerator() = default;

    EntityID create();
    void destroy(EntityID entity);
    bool isAlive(EntityID entity) const;

private:
    std::vector<uint32_t> generations;
    std::vector<uint32_t> freeList;
};