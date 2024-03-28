
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
    target_link_libraries(TestGUI SDL2::SDL2main SDL2::SDL2 SDL2_ttf::SDL2_ttf-static)
endif()

if(EMSCRIPTEN)
    add_executable(TestWASM wasm.cpp $<TARGET_OBJECTS:cc-foundation> $<TARGET_OBJECTS:cc-graphics>)
    target_link_libraries(TestWASM SDL2::SDL2main SDL2::SDL2-static SDL2_ttf::SDL2_ttf-static)
endif()
