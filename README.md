# SDL-Cellular-Automata-Game-of-Life

Conwey's Game of life implemented in C++ usind SDL3

<img src="./screenshorts/Screenshot1.png" width="644px">

## CLONING

There are submodule present in the repo so be sure to clone it recursively with the following command:

```
git clone --recursive https://github.com/KATZ5/SDL-Cellular-Automata-Game-of-Life.git
```

Updating submodules manually:

```
git submodule init
git submodule update
```

## BUILDING

The repository contains everything required to compile and build the examples on **Windows**, **Linux** using a compiler that supports c++98 and cmake as the build system

### Windows, Linux

Use the provided CMakeLists.txt with CMake to generate a build configuration for your favorite IDE or compiler, e.g.:

Windows using Visual Studio:

```
cmake -G "Visual Studio 14 2015 Win64"
```

Windows using MinGW:

```
cmake .. -G "MinGW Makefiles"
```

Linux:

```
cd SDL-Cellular-Automata-Game-of-Life
mkdir build && cd build
cmake ..
make
`
