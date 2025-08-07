#include "buffers/vao.hpp"

    VertexArrayObject::VertexArrayObject()
    {
        glGenVertexArrays(1, &id);
    }

    VertexArrayObject::~VertexArrayObject()
    {
        destroy();
    }

    void VertexArrayObject::bind()
    {
        glBindVertexArray(id);
    }

    void VertexArrayObject::unbind()
    {
        glBindVertexArray(0);
    }

    void VertexArrayObject::destroy()
    {
        glDeleteVertexArrays(1, &id);
    }

    GLuint VertexArrayObject::getID()
    {
        return id;
    }