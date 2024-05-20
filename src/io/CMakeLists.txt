
list(APPEND socket_source socket.cpp)

if (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    list(APPEND socket_source socket_mswin.cpp)

else ()
    list(APPEND socket_source socket_posix.cpp)
endif ()

add_library(cc-io OBJECT
    file_channel.cpp
    tcp_channel.cpp
    tcp_server_channel.cpp
    udp_channel.cpp
    ${socket_source})
