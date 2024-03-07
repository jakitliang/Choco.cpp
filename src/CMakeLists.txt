
add_library(
        cc-src OBJECT
        main.cpp
        intptr.cpp
        pointer.cpp
        var.cpp
        string.cpp
)

target_include_directories(cc-src PUBLIC ../)
