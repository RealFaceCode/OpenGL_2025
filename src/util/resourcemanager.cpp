#include "util/resourcemanager.hpp"

#include "buffers/material.hpp"
#include "defines.hpp"
#include "util/fileio.hpp"
#include <functional>

ResourceManager::ResourceManager()
: textureMap(), materials(), materialIDMap()
{}

ResourceManager::~ResourceManager() = default;

Expected<std::reference_wrapper<const Texture>> ResourceManager::loadTexture(std::string_view textureName, Path path)
{
    std::string name = std::string(textureName);

    auto[it, inserted] = textureMap.try_emplace(name, Texture());
    if(!inserted)
        return Unexpected(std::format("ResourceManager: Failed to load texture with filepath: {} and texture name: {}. A texture with this name already exists.", path.string(), name));

    auto img = ReadImage(path);
    if(!img)
    {
        textureMap.erase(it);
        return Unexpected(std::format("ResourceManager: {}", img.error()));
    }

    Texture& texture = it->second;
    auto tex = texture.create(*img);
    if(!tex)
    {
        textureMap.erase(it);
        return Unexpected(std::format("ResourceManager: {}", tex.error()));
    }

    return Expected<std::reference_wrapper<const Texture>>(std::cref(texture));
}

Expected<std::reference_wrapper<const Material>> ResourceManager::createMaterial(std::string_view materialName, std::string_view textureName)
{
    std::string name = std::string(materialName);
    std::string texName = std::string(textureName);

    auto texture = textureMap.find(texName);
    if(texture == textureMap.end())
        return Unexpected(std::format("ResourceManager: Failed to create material with name: {}. A texture with name {} doesn't exist", name, texName));

    auto materialID = materialIDMap.find(name);
    if(materialID != materialIDMap.end())
        return Unexpected(std::format("ResourceManager: Failed to create material with name: {}. Material already exists.", name));

    materialNames.emplace_back(name);
    materials.emplace_back(Material{
        .texture = texture->second.getHandle()
    });

    size_t id = materials.size() - 1;
    materialIDMap[name] = id;

    return Expected<std::reference_wrapper<const Material>>(std::cref(materials.back()));
}

void ResourceManager::unloadTexture(std::string_view textureName)
{
    std::string name = std::string(textureName);

    if(textureMap.contains(name))
        textureMap.erase(name);
}

void ResourceManager::destroyMaterial(std::string_view materialName)
{
    std::string name = std::string(materialName);

    auto materialID = materialIDMap.find(name);
    if(materialID == materialIDMap.end())
        return;

    size_t ID = materialID->second;

    if (ID == materials.size() - 1)
    {
        materials.pop_back();
        materialNames.pop_back();
        materialIDMap.erase(name);
        return;
    }

    std::string lastMaterialName = materialNames.back();

    materials.at(ID) = std::move(materials.back());
    materials.pop_back();

    materialNames.at(ID) = std::move(materialNames.back());
    materialNames.pop_back();

    materialIDMap[lastMaterialName] =ID;
    materialIDMap.erase(name);
}

Expected<std::reference_wrapper<const Texture>> ResourceManager::getTexture(std::string_view textureName) const
{
    std::string name = std::string(textureName);

    auto texture = textureMap.find(name);
    if(texture == textureMap.end())
        return Unexpected(std::format("ResourceManager: Failed to find texture with name: {}", name));

    return Expected<std::reference_wrapper<const Texture>>(std::cref(texture->second));
}

Expected<std::reference_wrapper<const Material>> ResourceManager::getMaterial(std::string_view materialName) const
{
    std::string name = std::string(materialName);

    auto materialID = materialIDMap.find(name);
    if(materialID == materialIDMap.end())
        return Unexpected(std::format("ResourceManager: Failed to find material with name: {}", name));

    return Expected<std::reference_wrapper<const Material>>(std::cref(materials[materialID->second]));
}

Expected<GLuint> ResourceManager::getTextureID(std::string_view textureName) const
{
    std::string name = std::string(textureName);

    auto texture = textureMap.find(name);
    if(texture == textureMap.end())
        return Unexpected(std::format("ResourceManager: Failed to find texture with name: {}", name));

    return Expected<GLuint>(texture->second.getID());
}

Expected<GLuint64> ResourceManager::getTextureHandle(std::string_view textureName) const
{
    std::string name = std::string(textureName);

    auto texture = textureMap.find(name);
    if(texture == textureMap.end())
        return Unexpected(std::format("ResourceManager: Failed to find texture with name: {}", name));

    return Expected<GLuint>(texture->second.getHandle());
}

Expected<size_t> ResourceManager::getMaterialID(std::string_view materialName) const
{
    std::string name = std::string(materialName);

    auto materialID = materialIDMap.find(name);
    if(materialID == materialIDMap.end())
        return Unexpected(std::format("ResourceManager: Failed to find materialID with name: {}", name));

    return Expected<size_t>(materialID->second);
}

const std::vector<Material>& ResourceManager::getMaterials()
{
    return materials;
}