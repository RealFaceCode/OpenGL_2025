#pragma once

#include <unordered_map>
#include <string>

#include "defines.hpp"
#include "buffers/texture.hpp"
#include "buffers/material.hpp"

class ResourceManager
{
public:
    ResourceManager();
    ~ResourceManager();

    Expected<std::reference_wrapper<const Texture>> loadTexture(std::string_view textureName, Path path);
    Expected<std::reference_wrapper<const Material>> createMaterial(std::string_view materialName, std::string_view textureName);

    void unloadTexture(std::string_view textureName);
    void destroyMaterial(std::string_view materialName);

    Expected<std::reference_wrapper<const Texture>> getTexture(std::string_view textureName) const;
    Expected<std::reference_wrapper<const Material>> getMaterial(std::string_view materialName) const;
    Expected<GLuint> getTextureID(std::string_view textureName) const;
    Expected<GLuint64> getTextureHandle(std::string_view textureName) const;
    Expected<size_t> getMaterialID(std::string_view materialName) const;

    const std::vector<Material>& getMaterials();

private:
    std::unordered_map<std::string, Texture> textureMap;
    std::vector<std::string> materialNames;
    std::vector<Material> materials;
    std::unordered_map<std::string, size_t> materialIDMap;
};