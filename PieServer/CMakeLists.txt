cmake_minimum_required (VERSION 3.5)

set(project_name PieJam)
set(version 0.0.1)
project (${project_name} VERSION ${version})

set(CMAKE_CXX_STANDARD 14) # C++14...
set(CMAKE_CXX_STANDARD_REQUIRED ON) #...is required...
set(CMAKE_CXX_EXTENSIONS OFF) #...without compiler extensions like gnu++11
add_definitions(-Wall)

file (GLOB SOURCES "src/*.cpp")

add_executable(${project_name} ${SOURCES})

