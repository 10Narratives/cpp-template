cmake_minimum_required(VERSION 3.30 FATAL_ERROR)
project(
    TemplateProject
    VERSION 0.0.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

set(CONFIG_SOURCE_DIR "${CMAKE_SOURCE_DIR}/configs")
set(CONFIG_DEST_DIR "${CMAKE_BINARY_DIR}/configs")

file(GLOB CONFIG_FILES "${CONFIG_SOURCE_DIR}/*.toml")

set(OUTPUT_FILES "")
foreach(FILE ${CONFIG_FILES})
    get_filename_component(FILENAME ${FILE} NAME)
    list(APPEND OUTPUT_FILES "${CONFIG_DEST_DIR}/${FILENAME}")
endforeach()

add_custom_command(
    OUTPUT ${OUTPUT_FILES}
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CONFIG_DEST_DIR}
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CONFIG_SOURCE_DIR} ${CONFIG_DEST_DIR}
    COMMENT "Copying configuration files to build directory"
)

add_custom_target(CopyConfigFiles ALL DEPENDS ${OUTPUT_FILES})

add_executable(${PROJECT_NAME} source/main.cpp)
add_dependencies(${PROJECT_NAME} CopyConfigFiles)
