
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
        font.cpp
        ui_event.cpp
        application.cpp
        window.cpp
        window_context.h
        window_context.cpp
        renderer.cpp
        renderer_context.h
        renderer_context.cpp
        texture.cpp
        image.cpp
        image_data.cpp
        image_batch.cpp
        vector2.cpp
        vector3.cpp
        vector4.cpp
        canvas.cpp
        pixels.cpp
        color.cpp
        vertex.cpp
#        internal.h
#        view.cpp
        graphics.cpp
        rect.cpp
        ui_element.cpp
)

target_include_directories(cc-foundation PUBLIC ../)
target_include_directories(cc-graphics PUBLIC ../)

#target_link_libraries(cc-graphics)

