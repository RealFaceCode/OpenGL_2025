#version 460 core
#extension GL_ARB_bindless_texture : require
#extension GL_ARB_gpu_shader_int64 : enable

in vec2 fTexCoords;
flat in uint fTextureID;

layout (location = 0) out vec4 color;

layout(std430, binding = 0) buffer TextureHandles {
    uint64_t textureHandles[];
};

void main()
{
    uint64_t handle = textureHandles[fTextureID];
    sampler2D tex = sampler2D(handle);
    color = texture(tex, fTexCoords);
}