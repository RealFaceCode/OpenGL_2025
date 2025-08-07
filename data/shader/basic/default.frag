#version 460 core

layout (location = 0) out vec4 color;

void main()
{
    color = vec4(1.0, 0.0, 0.0, 1.0); // Output a solid red color
}
// This fragment shader outputs a solid red color.
// It uses the output location 0 to set the color of the fragment.