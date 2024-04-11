
add_executable(TestZone zone.cpp $<TARGET_OBJECTS:cc-foundation>)

add_executable(TestVar var.cpp $<TARGET_OBJECTS:cc-foundation>)

add_executable(TestArray array.cpp $<TARGET_OBJECTS:cc-foundation>)

add_executable(TestList list.cpp $<TARGET_OBJECTS:cc-foundation>)

add_executable(TestString string.cpp $<TARGET_OBJECTS:cc-foundation>)

add_executable(TestCommon common.cpp $<TARGET_OBJECTS:cc-foundation>)

add_executable(TestLinkedList test_linked_list.cpp $<TARGET_OBJECTS:cc-foundation>)

add_executable(TestVector test_vector.cpp $<TARGET_OBJECTS:cc-foundation>)

add_executable(TestByte byte.cpp $<TARGET_OBJECTS:cc-foundation>)

add_executable(TestFileChannel file_channel.cpp $<TARGET_OBJECTS:cc-foundation>)

add_executable(TestGUI gui.cpp $<TARGET_OBJECTS:cc-foundation> $<TARGET_OBJECTS:cc-graphics>)

if(EMSCRIPTEN)
    target_link_libraries(TestGUI SDL2::SDL2main SDL2::SDL2-static SDL2_ttf::SDL2_ttf-static)
else()
    target_link_libraries(TestGUI
            SDL2::SDL2main
            SDL2::SDL2
            SDL2_ttf::SDL2_ttf-static
            SDL2_image::SDL2_image-static)
endif()

if(EMSCRIPTEN)
    add_executable(TestWASM wasm.cpp $<TARGET_OBJECTS:cc-foundation>)
    add_compile_definitions("__EMSCRIPTEN__")
    target_link_options(TestWASM PRIVATE
            "-sMODULARIZE=1"
            "-sEXPORT_NAME='Main'"
            "-sINVOKE_RUN=0"
            "-sDISABLE_DEPRECATED_FIND_EVENT_TARGET_BEHAVIOR=0"
            "-sEXPORTED_FUNCTIONS=['_main']"
            "-sEXPORTED_RUNTIME_METHODS=['callMain', 'ccall', 'cwrap']"
            "-sFORCE_FILESYSTEM=1"
            "-sUSE_SDL=2"
            "-sUSE_SDL_TTF=2"
            "-sALLOW_MEMORY_GROWTH=1"
            "-sASYNCIFY")
endif()
