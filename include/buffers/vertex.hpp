#pragma once

#include <glad/gl.h>
#include <glm/glm.hpp>

struct Vertex2D
{
    glm::vec2 position;
    glm::vec2 texCoords;
    //GLuint textureID;
    //GLuint modelID;
};

struct Vertex3D
{
    glm::vec3 position;
    glm::vec2 texCoords;
    GLuint textureID;
    GLuint modelID;
};