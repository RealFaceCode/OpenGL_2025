#include "util/fileio.hpp"
#include "defines.hpp"
#include <cstring>
#include <expected>
#include <filesystem>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>

Expected<std::vector<unsigned char>> ReadFile(Path path, bool newLine)
{
    if(!std::filesystem::exists(path))
        return Unexpected(std::format("Failed to find file with filepath: {}", path.string()));

    size_t fileSize = std::filesystem::file_size(path);

    std::vector<unsigned char> data;
    data.reserve(newLine ? fileSize + 1 : fileSize);
    data.resize(newLine ? fileSize + 1 : fileSize);

    FILE* file = nullptr;
    fopen_s(&file, path.string().c_str(), "rb");
    if(!file)
        return Unexpected(std::format("Failed to open file with filepath: {}", path.string()));

    size_t read = fread(data.data(), fileSize, 1, file);
    if(read != 1)
        return Unexpected(std::format("Failed to read file with filepath: {}", path.string()));

    if(newLine)
        data[fileSize - 1] = '\n';

    return Expected<std::vector<unsigned char>>(data);
}

Expected<size_t> WriteFile(const std::vector<unsigned char>& data, Path path)
{
    FILE* file = nullptr;
    fopen_s(&file, path.string().c_str(), "wb");
    if(!file)
        return Unexpected(std::format("Failed to open file with filepath: {}", path.string()));

    size_t write = fwrite(data.data(), data.size(), 1, file);
    if(write != 1)
        return Unexpected(std::format("Failed to read from file with filepath: {}", path.string()));

    return Expected<size_t>(write);
}

Expected<ImageData> ReadImage(Path path)
{
    if(!std::filesystem::exists(path))
        return Unexpected(std::format("Failed to find file with filepath: {}", path.string()));

    stbi_set_flip_vertically_on_load(true);

    ImageData data;
    auto imgData = stbi_load(path.string().c_str(), &data.width, &data.height, &data.numChannels, 0);
    if(!imgData)
        return Unexpected(std::format("Failed to load Image with filepath: {}", path.string()));

    size_t size = data.width * data.height * data.numChannels;
    data.data.reserve(size);
    data.data.resize(size);
    
    const char* result = reinterpret_cast<const char*>(memcpy(data.data.data(), imgData, size));
    stbi_image_free(imgData);
    if(!result || data.data.empty())
        return Unexpected(std::format("Failed to copy context to buffer from image with filepath: {}", path.string()));

    return Expected<ImageData>(data);
}

Expected<size_t> WriteImage(const ImageData& img, Path path)
{
    if(img.data.empty())
        return Unexpected(std::format("Failed to write Image to file with filepath: {}, image data is empty", path.string()));

    int stride = img.width * img.numChannels;
    int result = stbi_write_png(path.string().c_str(), img.width, img.height, img.numChannels, img.data.data(), stride);
    
    if (result == 0)
        return Unexpected(std::format("Failed to write image to filepath: {}", path.string()));
    
    return Expected<size_t>(img.data.size());
}