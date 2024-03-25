
add_library(
        cc-src OBJECT
        intptr.cpp
        zone.cpp
        string.cpp
        data.cpp
        file_io.cpp
        channel.cpp
        file_channel.cpp
)

target_include_directories(cc-src PUBLIC ../)
