[![Linux](https://github.com/MarcUbach/GoogleMock-Example/actions/workflows/build.yml/badge.svg)](https://github.com/MarcUbach/GoogleMock-Example/actions/workflows/build.yml)
[![Windows(Visual Studio 2019)](https://github.com/MarcUbach/GoogleMock-Example/actions/workflows/windows.yml/badge.svg)](https://github.com/MarcUbach/GoogleMock-Example/actions/workflows/windows.yml)
[![Tests](https://github.com/MarcUbach/GoogleMock-Example/actions/workflows/tests.yml/badge.svg)](https://github.com/MarcUbach/GoogleMock-Example/actions/workflows/tests.yml)

# "A Unit Testing Practitioner's Guide to Everyday Mockito" Example in C++ with GMock

This repository contains the example explained in toptal´s article [A Unit Testing Practitioner's Guide to Everyday Mockito](https://www.toptal.com/java/a-guide-to-everyday-mockito) implemented in C++ with the use of GMock

## Dependencies

- [CMake](https://cmake.org/) >= 3.14 installed. 
- A C++17 compatible compiler

## Building

### Building for POSIX

```bash
mkdir -p build && cd build
cmake -DCMAKE_BUILD_TYPE=Release .. && cmake --build .
```
