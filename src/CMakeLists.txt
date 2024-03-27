
add_library(
        cc-foundation OBJECT
        intptr.cpp
        zone.cpp
        string.cpp
        data.cpp
        file_io.cpp
        channel.cpp
        file_channel.cpp
)

add_library(
        cc-graphics OBJECT
        application.cpp
        window.cpp
        renderer.cpp
        texture.cpp
        canvas.cpp
        pixels.cpp
        internal.h
)

target_include_directories(cc-foundation PUBLIC ../)
target_include_directories(cc-graphics PUBLIC ../)

#target_link_libraries(cc-graphics)

