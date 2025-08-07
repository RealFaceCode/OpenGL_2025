#pragma once

#include <glad/gl.h>

class VertexBufferObject
{
public:
    VertexBufferObject();
    ~VertexBufferObject();

    void bind();
    void unbind();

    void data(GLsizei size, const void* data, GLenum usage);
    void subdata(GLintptr offset, GLsizei size, const void* data);
    void addAttrib(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void *offset);

    void destroy();
    GLuint getID();
private:
    GLuint id;
};