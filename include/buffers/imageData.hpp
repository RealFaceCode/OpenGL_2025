#pragma once

#include <vector>

struct ImageData
{
    int width;
    int height;
    int numChannels;
    std::vector<unsigned char> data;
};