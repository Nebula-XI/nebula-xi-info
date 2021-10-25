# nebula-xi-info

Units Tree Configuration (UTC) and Units Information Structures (UIS) for AXI Library

[![CMake](https://github.com/Nebula-XI/nebula-xi-info/actions/workflows/cmake.yml/badge.svg)](https://github.com/Nebula-XI/nebula-xi-info/actions/workflows/cmake.yml)

### Required

CMake 3.21, Ninja 1.10.2, Boost 1.75, GCC 10.3 (Linux Native Build) or MinGW Cross-Compiler 10.3 (Build for Windows on Linux)

### Configure

#### Linux Native x86_64

`cmake --preset linux-x64-release`

`cmake --preset linux-x64-debug`

#### Windows on Linux x86_64

`cmake --preset windows-x64-release`

`cmake --preset windows-x64-debug`

### Building

#### Linux Native x86_64

`cmake --build --preset linux-x64-release`

`cmake --build --preset linux-x64-release-rebuild`

`cmake --build --preset linux-x64-release-verbose`

`cmake --build --preset linux-x64-debug`

`cmake --build --preset linux-x64-debug-rebuild`

`cmake --build --preset linux-x64-debug-verbose`

#### Windows on Linux x86_64

`cmake --build --preset windows-x64-release`

`cmake --build --preset windows-x64-release-rebuild`

`cmake --build --preset windows-x64-release-verbose`

`cmake --build --preset windows-x64-debug`

`cmake --build --preset windows-x64-debug-rebuild`

`cmake --build --preset windows-x64-debug-verbose`

### Testing

#### Linux Native x86_64

`ctest --preset linux-x64-release`

`ctest --preset linux-x64-debug`

#### Windows on Linux x86_64

`ctest --preset windows-x64-release`

`ctest --preset windows-x64-debug`

### All

#### Linux

`./make sh config build test`


