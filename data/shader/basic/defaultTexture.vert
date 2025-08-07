#version 460 core

layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aTexCoords;

out vec2 fTexCoords;

void main()
{
    gl_Position = vec4(aPos, 0, 1.0);
    fTexCoords = aTexCoords;
}
// This vertex shader simply takes a 3D position input and outputs it as a 4D vector for rendering.
// The input position is expected to be in the attribute location 0.