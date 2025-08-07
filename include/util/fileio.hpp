#pragma once

#include <expected>
#include <vector>

#include <defines.hpp>
#include <buffers/imageData.hpp>

Expected<std::vector<unsigned char>> ReadFile(Path path, bool newLine = true);
Expected<size_t> WriteFile(const std::vector<unsigned char>& data, Path path);

Expected<ImageData> ReadImage(Path path);
Expected<size_t> WriteImage(const ImageData& image, Path path);