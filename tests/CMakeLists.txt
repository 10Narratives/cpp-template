find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

if(ENABLE_COVERAGE)
    if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
        # Add compiler flags for coverage
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fprofile-arcs -ftest-coverage")
        message(STATUS "Code coverage enabled")
    else()
        message(WARNING "Code coverage is not supported for this compiler: ${CMAKE_CXX_COMPILER_ID}")
    endif()
else()
    message(STATUS "Code coverage disabled")
endif()

file(GLOB TEST_SOURCES "test_lib/*.cpp")
add_executable(runTests ${TEST_SOURCES} test_main.cpp)
target_link_libraries(runTests PRIVATE
    ${GTEST_BOTH_LIBRARIES}
    pthread
    lib
)

enable_testing()
add_test(NAME runTests COMMAND runTests)

add_custom_target(runAllTests
    COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure
    COMMENT "Running all tests"
)

if(ENABLE_COVERAGE)
    set(COVERAGE_DIR "${CMAKE_BINARY_DIR}/coverage")
    file(MAKE_DIRECTORY ${COVERAGE_DIR})

    add_custom_target(coverage
        COMMAND lcov --capture --directory . --output-file ${COVERAGE_DIR}/coverage.info
        COMMAND lcov --remove ${COVERAGE_DIR}/coverage.info '*/tests/*' '/usr/*' --output-file ${COVERAGE_DIR}/filtered.info
        COMMAND genhtml ${COVERAGE_DIR}/filtered.info --output-directory ${COVERAGE_DIR}/html
        COMMAND ${CMAKE_COMMAND} -E echo "Coverage report generated at: ${COVERAGE_DIR}/html/index.html"
        WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
        COMMENT "Generating code coverage report"
    )
endif()