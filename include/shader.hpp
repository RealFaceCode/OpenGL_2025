#pragma once

#include <glad/gl.h>
#include <vector>
#include <print>

#include "defines.hpp"

class Shader
{
public:
    Shader();
    ~Shader();

    bool attach(GLenum type, Path path);
    bool link();

    void bind();
    void unbind();

    void destroy();
    GLuint getID();
    
private:
    std::string loadShaderSource(Path filepath);
    std::string glEnumToString(GLenum enumValue);
    bool checkShaderErrors(GLuint shader, const std::string& type);
    bool checkProgramError(GLuint program);

private:
    GLuint id;
    std::vector<GLuint> attachments;
};