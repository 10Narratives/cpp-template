cmake_minimum_required(VERSION 3.30 FATAL_ERROR)
project(
    TemplateProject
    VERSION 0.0.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -Wextra -g -O0")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -DNDEBUG")

if(WIN32)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHsc")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
endif()

option(BUILD_DOC "Build documentation" OFF)        
option(BUILD_TESTS "Build tests" OFF)              
option(ENABLE_COVERAGE "Enable code coverage" OFF) 

set(BUILD_TESTS ON)
set(ENABLE_COVERAGE ON)

add_subdirectory(configs)

add_subdirectory(source/lib)

add_executable(${PROJECT_NAME} source/main.cpp)

add_dependencies(${PROJECT_NAME} CopyConfigFiles)

if(BUILD_DOC)
    add_subdirectory(docs)
    add_dependencies(${PROJECT_NAME} DocsGeneration)
else()
    message(STATUS "Documentation building is disabled")
endif()
if(BUILD_TESTS)
    add_subdirectory(tests)
else()
    message(STATUS "Tests building is disabled")
endif()

if(WIN32)
    message(STATUS "Building for Windows")
    target_link_libraries(${PROJECT_NAME} PRIVATE ws2_32)
elseif(UNIX)
    message(STATUS "Building for Linux")
    target_link_libraries(${PROJECT_NAME} PRIVATE pthread)
endif()