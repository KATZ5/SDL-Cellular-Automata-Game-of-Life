cmake_minimum_required(VERSION 3.15)
project(SDLGameOfLife)

set(CMAKE_CXX_STANDARD 17)

# Use SDL3 static to keep things self-contained
# Default to static SDL3 unless overridden by user
option(SDL_STATIC "Build SDL as a static library" ON)
option(SDL_SHARED "Build SDL as a shared library" OFF)

# Optional: suppress SDL test targets
option(SDL_TEST "Build SDL test programs" OFF)

# Add SDL3
add_subdirectory(external/SDL3)

# Sources
file(GLOB SOURCES "src/*.cpp")

# Create executable
add_executable(SDLGameOfLife ${SOURCES})

# Link SDL3
target_link_libraries(SDLGameOfLife SDL3-static)

# Include SDL3 headers
target_include_directories(SDLGameOfLife PRIVATE external/SDL3/include)

