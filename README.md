# OpenGL C++23 Projekt

Ein modernes OpenGL-Projekt mit CMake, das GLFW und GLM automatisch herunterlädt und konfiguriert.

## Features

- **C++23 Standard**: Nutzt die neuesten C++ Features
- **Automatische Dependency-Verwaltung**: GLFW und GLM werden automatisch über FetchContent heruntergeladen
- **Flexible Projektstruktur**: Findet automatisch alle .cpp/.c Dateien in src/ und source/ Ordnern
- **Cross-Platform**: Unterstützt Windows, Linux und macOS
- **Organisierte Ausgabe**: Binärdateien in `bin/`, Bibliotheken in `lib/`
- **Dependencies-Ordner**: Lokale Abhängigkeiten können im `dependencies/` Ordner verwaltet werden

## Projektstruktur

```
OpenGL/
├── CMakeLists.txt          # Haupt-CMake-Konfiguration
├── src/                    # Quelldateien (.cpp, .c)
│   └── main.cpp           # Beispiel-Hauptdatei
├── include/               # Header-Dateien (.h, .hpp)
├── dependencies/          # Lokale Abhängigkeiten
├── bin/                   # Ausführbare Dateien (wird erstellt)
└── lib/                   # Bibliotheksdateien (wird erstellt)
```

## Abhängigkeiten

### Automatisch heruntergeladen:
- **GLFW 3.4**: Fenster- und Eingabeverwaltung
- **GLM 1.0.1**: Mathematikbibliothek für OpenGL

### System-Abhängigkeiten:
- **Windows**: OpenGL32, GDI32, User32, Kernel32, Shell32
- **Linux**: OpenGL, DL (Dynamic Linking)
- **macOS**: OpenGL, Cocoa, IOKit, CoreVideo

## Build-Anweisungen

### Windows (mit Visual Studio)

```powershell
# Projekt konfigurieren
cmake -B build -S . -G "Visual Studio 17 2022"

# Bauen
cmake --build build --config Release

# Oder Debug-Version
cmake --build build --config Debug
```

### Windows (mit MinGW/Clang)

```powershell
# Projekt konfigurieren
cmake -B build -S . -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release

# Bauen
cmake --build build
```

### Linux/macOS

```bash
# Projekt konfigurieren
cmake -B build -S . -DCMAKE_BUILD_TYPE=Release

# Bauen
cmake --build build

# Mit mehreren Threads bauen
cmake --build build -j$(nproc)
```

## Ausführen

Nach dem erfolgreichen Build finden Sie die ausführbare Datei in:
- **Windows**: `build/bin/OpenGLProject.exe`
- **Linux/macOS**: `build/bin/OpenGLProject`

```powershell
# Windows
.\build\bin\OpenGLProject.exe

# Linux/macOS
./build/bin/OpenGLProject
```

## Dependencies-Ordner verwenden

Um lokale Abhängigkeiten zu verwenden, erstellen Sie Unterordner im `dependencies/` Verzeichnis:

```
dependencies/
├── my_library/
│   ├── include/           # Header-Dateien
│   ├── lib/              # .lib/.a Dateien
│   └── CMakeLists.txt    # Optional: Eigene CMake-Konfiguration
└── another_lib/
    └── include/
```

Die CMakeLists.txt erkennt automatisch:
- Include-Verzeichnisse in `dependencies/*/include/`
- Bibliotheksdateien (`.lib`, `.a`, `.so`, `.dylib`)
- CMakeLists.txt Dateien für Sub-Projekte

## Compiler-Unterstützung

### Mindestanforderungen:
- **MSVC**: Visual Studio 2022 (Version 17.0+)
- **GCC**: Version 13+
- **Clang**: Version 17+

### C++23 Features werden unterstützt:
- Modules (falls verfügbar)
- Ranges und Views
- Concepts
- Coroutines
- Und viele weitere moderne C++ Features

## Konfigurationsoptionen

Sie können das Verhalten durch CMake-Variablen anpassen:

```powershell
# Debug-Build mit zusätzlichen Informationen
cmake -B build -S . -DCMAKE_BUILD_TYPE=Debug

# Eigenen Projektnamen setzen
cmake -B build -S . -DPROJECT_NAME=MeinProjekt

# Dependency-Verzeichnis ändern
cmake -B build -S . -DDEPENDENCIES_DIR=/pfad/zu/deps
```

## Problembehandlung

### CMake-Version zu alt
Stellen Sie sicher, dass CMake 3.20+ installiert ist:
```powershell
cmake --version
```

### C++23 nicht unterstützt
Falls Ihr Compiler C++23 nicht unterstützt, ändern Sie in der CMakeLists.txt:
```cmake
set(CMAKE_CXX_STANDARD 20)  # Oder 17
```

### GLFW/GLM Download-Probleme
Bei Netzwerkproblemen können Sie die Bibliotheken manuell herunterladen und im `dependencies/` Ordner platzieren.
