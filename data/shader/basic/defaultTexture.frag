#version 460 core
#extension GL_ARB_bindless_texture : require
#extension GL_ARB_gpu_shader_int64 : enable

in vec2 fTexCoords;

layout (location = 0) out vec4 color;

uniform uint64_t uTexture;

void main()
{
    sampler2D tex = sampler2D(uTexture)
    color = texture(tex, fTexCoords);
}
// This fragment shader outputs a solid red color.
// It uses the output location 0 to set the color of the fragment.