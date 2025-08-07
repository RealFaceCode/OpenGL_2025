#include "buffers/ebo.hpp"

ElementBufferObject::ElementBufferObject()
{
    glGenBuffers(1, &id);
 }

ElementBufferObject::~ElementBufferObject()
{
    destroy();
}

void ElementBufferObject::bind()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
}

void ElementBufferObject::unbind()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void ElementBufferObject::data(GLsizei size, const void* data, GLenum usage)
{
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, usage);
}

void ElementBufferObject::subdata(GLintptr offset, GLsizei size, const void* data)
{
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, offset, size, data);
}

void ElementBufferObject::destroy()
{
    glDeleteBuffers(1, &id);
}

GLuint ElementBufferObject::getID()
{
    return id;
}