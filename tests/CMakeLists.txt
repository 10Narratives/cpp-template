find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

file(GLOB TEST_SOURCES "test_lib/*.cpp")
message(STATUS "${TEST_SOURCES}")
add_executable(runTests ${TEST_SOURCES} test_main.cpp)
target_link_libraries(runTests PRIVATE  ${GTEST_BOTH_LIBRARIES} pthread)
target_link_libraries(runTests PRIVATE lib)

enable_testing()
add_test(NAME runTests COMMAND runTests)