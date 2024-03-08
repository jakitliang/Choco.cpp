
add_library(
        cc-src OBJECT
        main.cpp
        intptr.cpp
        pointer.cpp
        string.cpp
)

target_include_directories(cc-src PUBLIC ../)
