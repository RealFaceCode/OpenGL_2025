#include "buffers/ssbo.hpp"
#include "glad/gl.h"

ShaderStorageBufferObject::ShaderStorageBufferObject(GLuint blockID)
: id(0), blockID(blockID)
{
    glGenBuffers(1, &id);
}

ShaderStorageBufferObject::~ShaderStorageBufferObject()
{
    destroy();
}

void ShaderStorageBufferObject::data(GLsizei size, const void* data, GLenum usage)
{
    glBufferData(GL_SHADER_STORAGE_BUFFER, size, data, usage);
}

void ShaderStorageBufferObject::subdata(GLsizei offset, GLsizei size, const void* data)
{
    glBufferSubData(GL_SHADER_STORAGE_BUFFER, offset, size, data);
}

void ShaderStorageBufferObject::bind()
{
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, id);
}

void ShaderStorageBufferObject::unbind()
{
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
}

void ShaderStorageBufferObject::bindBufferBase()
{
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, blockID, id);
}

void ShaderStorageBufferObject::destroy()
{
    if(id)
        glDeleteBuffers(1, &id);
}

GLuint ShaderStorageBufferObject::getID()
{
    return id;
}

GLuint ShaderStorageBufferObject::getStorageBlockID()
{
    return blockID;
}