cmake_minimum_required(VERSION 3.23)
project(Choco.cpp)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

add_subdirectory(src)

#add_executable(cc $<TARGET_OBJECTS:cc-src>)

add_library(cc $<TARGET_OBJECTS:cc-src>)

add_subdirectory(test)
