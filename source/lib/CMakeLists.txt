file(GLOB LIB_HEADER_FILES "include/*.h")
file(GLOB LIB_SOURCE_FILES "src/*.cpp")
add_library(lib STATIC ${LIB_HEADER_FILES} ${LIB_SOURCE_FILES})
target_include_directories(lib PUBLIC include)