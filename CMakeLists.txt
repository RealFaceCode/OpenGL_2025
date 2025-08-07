cmake_minimum_required(VERSION 3.20)
project(OpenGLProject VERSION 1.0.0 LANGUAGES CXX C)

# C++23 Standard setzen
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Compile commands für IntelliSense generieren
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Output-Verzeichnisse im Root-Verzeichnis definieren
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)

# FetchContent Module einbinden
include(FetchContent)

# GLFW als Dependency fetchen
message(STATUS "Fetching GLFW...")
FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG 3.4
    SOURCE_DIR ${CMAKE_SOURCE_DIR}/dependencies/glfw
)

# GLFW Optionen setzen (vor dem Verfügbarmachen)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

# GLM als Dependency fetchen
message(STATUS "Fetching GLM...")
FetchContent_Declare(
    glm
    GIT_REPOSITORY https://github.com/g-truc/glm.git
    GIT_TAG 1.0.1
    SOURCE_DIR ${CMAKE_SOURCE_DIR}/dependencies/glm
)

# Dependencies verfügbar machen
FetchContent_MakeAvailable(glfw glm)

# OpenGL finden
find_package(OpenGL REQUIRED)

# GLAD
add_subdirectory(${CMAKE_SOURCE_DIR}/dependencies/glad)

# Quelldateien automatisch finden mit automatischer Neukonfiguration
file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS
    "${CMAKE_SOURCE_DIR}/src/*.cpp"
    "${CMAKE_SOURCE_DIR}/src/*.c"
)

file(GLOB_RECURSE HEADER_FILES CONFIGURE_DEPENDS
    "${CMAKE_SOURCE_DIR}/include/*.hpp"
    "${CMAKE_SOURCE_DIR}/include/*.h"
)


# Executable erstellen
add_executable(${PROJECT_NAME} ${SOURCE_FILES} ${HEADER_FILES})

# Include-Verzeichnisse hinzufügen
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/dependencies/glfw/include
    ${CMAKE_SOURCE_DIR}/dependencies/glm
    ${CMAKE_SOURCE_DIR}/dependencies/glad/include
    ${CMAKE_SOURCE_DIR}/dependencies/stb
)

# Libraries verlinken
target_link_libraries(${PROJECT_NAME} 
    glfw
    glm::glm
    OpenGL::GL
    glad
)

# Windows-spezifische Libraries
if(WIN32)
    target_link_libraries(${PROJECT_NAME} 
        gdi32
        user32
        kernel32
        winmm
    )
endif()

# Debug-Informationen ausgeben
message(STATUS "=== Projekt-Konfiguration ===")
message(STATUS "Projektname: ${PROJECT_NAME}")
message(STATUS "C++ Standard: ${CMAKE_CXX_STANDARD}")
message(STATUS "Build-Typ: ${CMAKE_BUILD_TYPE}")
message(STATUS "Ausgabeverzeichnis: ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
message(STATUS "Bibliotheksverzeichnis: ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}")
message(STATUS "Dependencies Verzeichnis: ${CMAKE_SOURCE_DIR}/dependencies")
message(STATUS "Build-Verzeichnis: ${CMAKE_BINARY_DIR}")
message(STATUS "Quelldateien gefunden: ${SOURCE_FILES}")
message(STATUS "============================")