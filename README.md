[![Build](https://github.com/MarcUbach/GoogleMock-Example/actions/workflows/build.yml/badge.svg)](https://github.com/MarcUbach/GoogleMock-Example/actions/workflows/build.yml)
[![Tests](https://github.com/MarcUbach/GoogleMock-Example/actions/workflows/tests.yml/badge.svg)](https://github.com/MarcUbach/GoogleMock-Example/actions/workflows/tests.yml)

# "A Unit Testing Practitioner's Guide to Everyday Mockito" Example in C++ with GMock

This repository contains the example explained in toptal´s article [A Unit Testing Practitioner's Guide to Everyday Mockito](https://www.toptal.com/java/a-guide-to-everyday-mockito) implemented in C++ with the use of GMock

## Dependencies

Make sure you have [CMake](https://cmake.org/) >= 3.14 installed. 

## Building

### Building for POSIX

```bash
mkdir -p build && cd build
cmake -DCMAKE_BUILD_TYPE=Release .. && cmake --build .
```
