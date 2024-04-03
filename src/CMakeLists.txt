
add_library(
        cc-foundation OBJECT
        intptr.cpp
        zone.cpp
        string.cpp
        data.cpp
        handle.cpp
        file_io.cpp
        channel.cpp
        file_channel.cpp
)

add_library(
        cc-graphics OBJECT
        screen.cpp
        flags.cpp
        ui_event.cpp
        application.cpp
        window.cpp
        window_context.h
        window_context.cpp
        renderer.cpp
        renderer_context.h
        renderer_context.cpp
#        texture.cpp
#        canvas.cpp
#        pixels.cpp
#        internal.h
#        view.cpp
#        graphics.cpp
#        ui_context.h
#        ui_context.cpp
)

target_include_directories(cc-foundation PUBLIC ../)
target_include_directories(cc-graphics PUBLIC ../)

#target_link_libraries(cc-graphics)

