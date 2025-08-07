#include "buffers/vbo.hpp"

VertexBufferObject::VertexBufferObject()
{
    glGenBuffers(1, &id);
}

VertexBufferObject::~VertexBufferObject()
{
    destroy();
}

void VertexBufferObject::bind()
{
    glBindBuffer(GL_ARRAY_BUFFER, id);
}

void VertexBufferObject::unbind()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBufferObject::data(GLsizei size, const void* data, GLenum usage)
{
    glBufferData(GL_ARRAY_BUFFER, size, data, usage);
}

void VertexBufferObject::subdata(GLintptr offset, GLsizei size, const void* data)
{
    glBufferSubData(GL_ARRAY_BUFFER, offset, size, data);
}

void VertexBufferObject::addAttrib(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void *offset)
{
    glEnableVertexAttribArray(index);
    glVertexAttribPointer(index, size, type, normalized, stride, offset);
}

void VertexBufferObject::destroy()
{
    glDeleteBuffers(1, &id);
}

GLuint VertexBufferObject::getID()
{
    return id;
}