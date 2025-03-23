cmake_minimum_required(VERSION 3.30 FATAL_ERROR)
project(
    TemplateProject
    VERSION 0.0.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

option(BUILD_DOC "Build documentation" OFF)
set(BUILD_DOC ON)

# Copies configuration files
add_subdirectory(configs)

# Setups the generation of documentation 
add_subdirectory(docs)

add_subdirectory(source/lib)

add_subdirectory(tests)

add_executable(${PROJECT_NAME} source/main.cpp)
add_dependencies(${PROJECT_NAME} CopyConfigFiles)

if(BUILD_DOC)
    add_dependencies(${PROJECT_NAME} DocsGeneration)
endif()

