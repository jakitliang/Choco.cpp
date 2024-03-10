cmake_minimum_required(VERSION 3.23)
project(cc)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)

add_subdirectory(src)

add_executable(cc $<TARGET_OBJECTS:cc-src> include/cc/object.h)
