#pragma once

#include<glad/gl.h>
#include <vector>


template<class VertexType>
class Mesh
{
public:
    Mesh();
    Mesh(const std::vector<VertexType>& vertices, const std::vector<GLuint>& indices);
    ~Mesh();

    const std::vector<VertexType>& getVertices() const;
    const std::vector<GLuint>& getIndices() const;

    size_t getVerticesCount() const;
    size_t getIndicesCount() const;
    size_t getSizeVertices() const;
    size_t getSizeIndices() const;

private:
    std::vector<VertexType> vertices;
    std::vector<GLuint> indices;
};