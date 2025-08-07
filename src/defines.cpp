#include "defines.hpp"

#include <print>

void glDebugOutput(GLenum source, 
                            GLenum type, 
                            unsigned int id, 
                            GLenum severity, 
                            GLsizei length, 
                            const char* message, 
                            const void* userParam)
{
    // Ignoriere nicht relevante Benachrichtigungen
    if (id == 131169 || id == 131185 || id == 131218 || id == 131204) return;

    std::println("------------------------------------------------------------------------------------");
    std::println("Debug-Meldung ({}: {})", id, message);

    switch (source)
    {
        case GL_DEBUG_SOURCE_API:             std::println("Quelle: API"); break;
        case GL_DEBUG_SOURCE_WINDOW_SYSTEM:   std::println("Quelle: Window System"); break;
        case GL_DEBUG_SOURCE_SHADER_COMPILER: std::println("Quelle: Shader Compiler"); break;
        case GL_DEBUG_SOURCE_THIRD_PARTY:     std::println("Quelle: Third Party"); break;
        case GL_DEBUG_SOURCE_APPLICATION:     std::println("Quelle: Application"); break;
        case GL_DEBUG_SOURCE_OTHER:           std::println("Quelle: Other"); break;
    }

    switch (type)
    {
        case GL_DEBUG_TYPE_ERROR:               std::println("Typ: Fehler"); break;
        case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: std::println("Typ: Veraltetes Verhalten"); break;
        case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  std::println("Typ: Undefiniertes Verhalten"); break;
        case GL_DEBUG_TYPE_PORTABILITY:         std::println("Typ: Portabilität"); break;
        case GL_DEBUG_TYPE_PERFORMANCE:         std::println("Typ: Performance"); break;
        case GL_DEBUG_TYPE_MARKER:              std::println("Typ: Marker"); break;
        case GL_DEBUG_TYPE_PUSH_GROUP:          std::println("Typ: Push Group"); break;
        case GL_DEBUG_TYPE_POP_GROUP:           std::println("Typ: Pop Group"); break;
        case GL_DEBUG_TYPE_OTHER:               std::println("Typ: Other"); break;
    }
    
    switch (severity)
    {
        case GL_DEBUG_SEVERITY_HIGH:         std::println("Schweregrad: HOCH"); break;
        case GL_DEBUG_SEVERITY_MEDIUM:       std::println("Schweregrad: MITTEL"); break;
        case GL_DEBUG_SEVERITY_LOW:          std::println("Schweregrad: NIEDRIG"); break;
        case GL_DEBUG_SEVERITY_NOTIFICATION: std::println("Schweregrad: Benachrichtigung"); break;
    }
    std::println("------------------------------------------------------------------------------------");
}