#version 460 core

layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aTexCoords;

out vec2 fTexCoords;

layout(std430, binding = 2) buffer PrimitiveToModelBuffer {
    uint primitiveToModelBuffer[];
};

layout(std430, binding = 3) buffer ModelMatrices {
    mat4 modelMatrices[];
};

void main()
{
    uint ID = gl_VertexID / 3;
    uint modelID = primitiveToModelBuffer[ID];
    mat4 model = modelMatrices[modelID];

    gl_Position = model * vec4(aPos, 0, 1.0);
    fTexCoords = aTexCoords;
}