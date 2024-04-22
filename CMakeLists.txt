cmake_minimum_required(VERSION 3.5)

# Project name
project(Apagnan)

# Set C++ version
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Source files
file(GLOB_RECURSE SOURCES "sources/*.cpp")

# Header files
file(GLOB_RECURSE HEADERS "headers/*.hpp")

# Add executable
add_executable(Apagnan ${SOURCES})

# Include directories
target_include_directories(Apagnan PRIVATE "headers")
