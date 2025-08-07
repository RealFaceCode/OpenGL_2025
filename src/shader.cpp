#include "shader.hpp"

Shader::Shader()
{
    id = glCreateProgram();
}

Shader::~Shader()
{
    destroy();
}

bool Shader::attach(GLenum type, Path path)
{
    std::string source = loadShaderSource(path);
    if(source.empty())
        return false;

    GLuint shader = glCreateShader(type);
    const char* shaderSource = source.c_str();

    glShaderSource(shader, 1, &shaderSource, nullptr);
    glCompileShader(shader);

    bool result = checkShaderErrors( shader, glEnumToString(type));
    if(result)
        attachments.emplace_back(shader);

    return result;
}

bool Shader::link()
{
    for(auto shader : attachments)
        glAttachShader(id, shader);

    glLinkProgram(id);
    bool result = checkProgramError(id);
    
    for(auto shader : attachments)
        glDeleteShader(shader);
    
    attachments.clear();
    return result;
}

void Shader::bind()
{
    glUseProgram(id);
}

void Shader::unbind()
{
    glUseProgram(0);
}

void Shader::destroy()
{
    glDeleteProgram(id);
}

GLuint Shader::getID()
{
    return id;
}

std::string Shader::loadShaderSource(Path filepath)
{
    std::string source;
    FILE* file = nullptr;
    fopen_s(&file, filepath.string().c_str(), "rb");
    if (!file)
    {
        std::println("Fehler beim Lesen der Datei: {}", filepath.string());
        return "";
    }

    fseek(file, 0, SEEK_END);
    size_t size = ftell(file);
    fseek(file, 0, SEEK_SET);

    source.resize(size);
    fread(source.data(), size, 1, file);
    fclose(file);
    return source;
}

std::string Shader::glEnumToString(GLenum enumValue)
{
    switch (enumValue) 
    {
    case GL_VERTEX_SHADER:
        return "GL_VERTEX_SHADER";
    case GL_FRAGMENT_SHADER:
        return "GL_FRAGMENT_SHADER";
    default:
        return "ERROR";
    }
}

bool Shader::checkShaderErrors(GLuint shader, const std::string& type)
{
    GLint success;
    GLchar infoLog[1024];

    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(shader, 1024, nullptr, infoLog);
        std::println("Fehler beim Kompilieren des {} Shaders: {}", type, infoLog);
        return false;
    }

    return true;
}

bool Shader::checkProgramError(GLuint program)
{
    GLint success;
    GLchar infoLog[1024];
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(program, 1024, nullptr, infoLog);
        std::println("Fehler beim Verknüpfen des Shader-Programms: {}", infoLog);
        return false;
    }

    return true;
}