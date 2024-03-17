
add_library(
        cc-src OBJECT
        intptr.cpp
        zone.cpp
        #        pointer.cpp
        string.cpp
)

target_include_directories(cc-src PUBLIC ../)
