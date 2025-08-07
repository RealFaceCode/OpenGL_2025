#include "buffers/texture.hpp"
#include <cstdio>

Texture::Texture()
: id(0), handle(0)
{
    glGenTextures(1, &id);
}

Texture::~Texture()
{
    if(handle)
        glMakeTextureHandleNonResidentARB(handle);
    
    if(id)
        glDeleteTextures(1, &id);
}

Texture::Texture(Texture&& other) noexcept
: id(other.id), handle(other.handle)
{
    other.id = 0;
    other.handle = 0;
}

Texture& Texture::operator=(Texture&& other) noexcept
{
    if (this != &other)
    {
        if (handle) glMakeTextureHandleNonResidentARB(handle);
        if (id) glDeleteTextures(1, &id);

        id = other.id;
        handle = other.handle;
        other.id = 0;
        other.handle = 0;
    }
    return *this;
}

Expected<std::pair<GLuint, GLuint64>> Texture::create(const ImageData& img)
{
    glBindTexture(GL_TEXTURE_2D, id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    GLenum format = GL_RGBA;
    switch(img.numChannels)
    {
        case 1: format = GL_RED; break;
        case 2: format = GL_RG; break;
        case 3: format = GL_RGB; break;
        case 4: format = GL_RGBA; break;
    }

    glTexImage2D(GL_TEXTURE_2D, 0, format, img.width, img.height, 0, format, GL_UNSIGNED_BYTE, img.data.data());
    glGenerateMipmap(GL_TEXTURE_2D);

    handle = glGetTextureHandleARB(id);
    if(handle == 0)
        return Unexpected("Failed to create texture handle");

    glMakeTextureHandleResidentARB(handle);
    glBindTexture(GL_TEXTURE_2D, 0);

    return Expected<std::pair<GLuint, GLuint64>>(std::pair<GLuint, GLuint64>(id, handle));
}

GLuint Texture::getID() const
{
    return id;
}

GLuint64 Texture::getHandle() const
{
    return handle;
}