# Global Project Configuration
cmake_minimum_required(VERSION 3.26)
project(Particles-Simulation)

# Find packages
find_package(SDL2 REQUIRED)

# Compiler options
set(CMAKE_CXX_STANDARD 23)

set(CMAKE_CXX_FLAGS_DEBUG "-ggdb -O0")
set(CMAKE_CXX_FLAGS_RELEASE "-O2 -ffast-math")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic")

# Set sources and includes
set(SOURCES
        src/main.cpp

        src/SDL-Layers/Color.cpp
        src/SDL-Layers/Point.cpp
        src/SDL-Layers/Rect.cpp
        src/SDL-Layers/vec2.cpp

        src/HSL.cpp

        src/Application.cpp
        src/Particle.cpp
)

set(INCLUDES
        include/
        include/SDL-Layers

        ${SDL2_INCLUDE_DIRS}
)

set(LIBRARIES
        ${SDL2_LIBRARIES}
        SDL2_image
        SDL2_ttf
)

# Sets up executable
add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC ${INCLUDES})
target_link_libraries(${PROJECT_NAME} PUBLIC ${LIBRARIES})

# Set output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)