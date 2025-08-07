#pragma once

#include <glad/gl.h>

class ElementBufferObject
{
public:
    ElementBufferObject();
    ~ElementBufferObject();

    void bind();
    void unbind();

    void data(GLsizei size, const void* data, GLenum usage);
    void subdata(GLintptr offset, GLsizei size, const void* data);

    void destroy();
    GLuint getID();
private:
    GLuint id;
};