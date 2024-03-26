
add_executable(TestZone zone.cpp $<TARGET_OBJECTS:cc-foundation>)

add_executable(TestVar var.cpp $<TARGET_OBJECTS:cc-foundation>)

add_executable(TestSlice slice.cpp $<TARGET_OBJECTS:cc-foundation>)

add_executable(TestArray array.cpp $<TARGET_OBJECTS:cc-foundation>)

add_executable(TestList list.cpp $<TARGET_OBJECTS:cc-foundation>)

add_executable(TestString string.cpp $<TARGET_OBJECTS:cc-foundation>)

add_executable(TestCommon common.cpp $<TARGET_OBJECTS:cc-foundation>)

add_executable(TestLinkedList test_linked_list.cpp $<TARGET_OBJECTS:cc-foundation>)

add_executable(TestVector test_vector.cpp $<TARGET_OBJECTS:cc-foundation>)

add_executable(TestByte byte.cpp $<TARGET_OBJECTS:cc-foundation>)

add_executable(TestFileChannel file_channel.cpp $<TARGET_OBJECTS:cc-foundation>)
