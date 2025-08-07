#version 460 core
#extension GL_ARB_bindless_texture : require
#extension GL_ARB_gpu_shader_int64 : enable

in vec2 fTexCoords;

layout (location = 0) out vec4 color;

struct Material
{
    uint64_t textureHandle;
};

layout (std430, binding = 0) buffer PrimitiveToMaterialBuffer {
    uint primitiveToMaterialBuffer[];
};

layout(std430, binding = 1) buffer MaterialDataBuffer {
    Material materialDataBuffer[];
};

void main()
{
    uint materialID = primitiveToMaterialBuffer[gl_PrimitiveID];
    Material currentMaterial = materialDataBuffer[materialID];
    sampler2D tex = sampler2D(currentMaterial.textureHandle);
    color = texture(tex, fTexCoords);
}
