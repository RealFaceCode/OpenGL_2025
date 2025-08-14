#pragma once

#include <expected>
#include <filesystem>
#include <string>
#include <glad/gl.h>

using Path = std::filesystem::path;

template<class Type, class ErrType = std::string>
using Expected = std::expected<Type, ErrType>;

template<class ErrType = std::string>
using Unexpected = std::unexpected<ErrType>;

using EntityID = std::size_t;

void glDebugOutput(GLenum source, GLenum type, unsigned int id, GLenum severity, GLsizei length, const char* message, const void* userParam);