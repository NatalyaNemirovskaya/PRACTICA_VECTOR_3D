cmake_minimum_required(VERSION 3.27)
project(
    Matrix
    VERSION 0.0.1
    DESCRIPTION "VECTOR_3D"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_BUILD_TYPE  Debug)

add_executable(VECTOR_3D)

set(sources
   src/main.cpp
   src/vector_3d.h
   src/vector_3d.cpp
   src/uniq_vector3D.h
   src/uniq_vector3D.cpp
)

target_sources(VECTOR_3D PRIVATE ${sources})

target_include_directories (VECTOR_3D
    PUBLIC
    
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>"
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>"

) 