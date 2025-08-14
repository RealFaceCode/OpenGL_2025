#pragma once

#include <glad/gl.h>
#include <vector>

struct Vertex2D;
struct Vertex3D;

template<class VertexType>
requires std::is_same_v<VertexType, Vertex2D> || std::is_same_v<VertexType, Vertex3D>
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
using Mesh2D = Mesh<Vertex2D>;
using Mesh3D = Mesh<Vertex3D>;