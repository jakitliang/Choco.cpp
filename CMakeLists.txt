cmake_minimum_required(VERSION 3.23)
project(Choco.cpp)

set(CMAKE_CXX_STANDARD 17)

# [Vendor]: SDL2
set(SDL2_INCLUDE_PATH "lib/SDL/include")
list(APPEND CMAKE_PREFIX_PATH "lib/SDL")
find_package(SDL2 REQUIRED)

# [Vendor]: SDL2_ttf
set(SDL2_TTF_INCLUDE_PATH "lib/SDL_ttf/include")
list(APPEND CMAKE_PREFIX_PATH "lib/SDL_ttf")
find_package(SDL2_ttf REQUIRED)

include_directories(
        include
        lib/SDL/include
        lib/SDL_ttf/include
)

add_subdirectory(src)

#add_executable(cc $<TARGET_OBJECTS:cc-src>)

add_library(cc $<TARGET_OBJECTS:cc-foundation>)

add_subdirectory(test)
