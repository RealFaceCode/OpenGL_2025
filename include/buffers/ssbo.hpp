#pragma once

#include "glad/gl.h"

class ShaderStorageBufferObject
{
public:
    ShaderStorageBufferObject(GLuint blockID);
    ~ShaderStorageBufferObject();

    void data(GLsizei size, const void* data, GLenum usage);
    void subdata(GLsizei offset, GLsizei size, const void* data);

    void bind();
    void unbind();

    void bindBufferBase();

    void destroy();
    GLuint getID();
    GLuint getStorageBlockID();

private:
    GLuint id;
    GLuint blockID;
};