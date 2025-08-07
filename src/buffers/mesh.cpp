#include "buffers/mesh.hpp"

#include "buffers/vertex.hpp"

template<typename VertexType>
Mesh<VertexType>::Mesh() = default;

template<typename VertexType>
Mesh<VertexType>::Mesh(const std::vector<VertexType>& vertices, const std::vector<GLuint>& indices)
: vertices(vertices), indices(indices)
{}

template<typename VertexType>
Mesh<VertexType>::~Mesh() = default;

template<typename VertexType>
const std::vector<VertexType>& Mesh<VertexType>::getVertices() const
{
    return vertices;
}

template<typename VertexType>
const std::vector<GLuint>& Mesh<VertexType>::getIndices() const
{
    return indices;
}

template<typename VertexType>
size_t Mesh<VertexType>::getVerticesCount() const
{
    return vertices.size();
}

template<typename VertexType>
size_t Mesh<VertexType>::getIndicesCount() const
{
    return indices.size();
}

template<typename VertexType>
size_t Mesh<VertexType>::getSizeVertices() const
{
    return vertices.size() * sizeof(VertexType);
}

template<typename VertexType>
size_t Mesh<VertexType>::getSizeIndices() const
{
    return indices.size() * sizeof(GLuint);
}

template class Mesh<Vertex2D>;
template class Mesh<Vertex3D>;