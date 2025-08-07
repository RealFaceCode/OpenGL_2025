#pragma once

#include "glad/gl.h"

class VertexArrayObject
{
public:
    VertexArrayObject();
    ~VertexArrayObject();

    void bind();
    void unbind();
    void destroy();
    GLuint getID();

private:
    GLuint id;
};