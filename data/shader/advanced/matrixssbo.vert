#version 460 core

layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aTexCoords;
layout (location = 2) in uint aTextureID;
layout (location = 3) in uint aModelID;

out vec2 fTexCoords;
flat out uint fTextureID;

layout(std430, binding = 1) buffer ModelMatrices {
    mat4 modelMatrices[];
};

void main()
{
    mat4 model = modelMatrices[aModelID];

    gl_Position = model * vec4(aPos, 0, 1.0);
    fTexCoords = aTexCoords;
    fTextureID = aTextureID;
}
