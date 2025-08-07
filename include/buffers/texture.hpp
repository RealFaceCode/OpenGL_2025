#pragma once

#include <glad/gl.h>

#include "defines.hpp"
#include "buffers/imageData.hpp"

class Texture
{
public:
    Texture();
    ~Texture();

    Texture(Texture&& other) noexcept;
    Texture& operator=(Texture&& other) noexcept;
    
    Expected<std::pair<GLuint, GLuint64>> create(const ImageData& img);
    GLuint getID() const;
    GLuint64 getHandle() const;

private:
    GLuint id;
    GLuint64 handle;
};