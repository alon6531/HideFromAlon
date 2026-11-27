cmake_minimum_required(VERSION 3.20)
project(HideFromAlon LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(POLICY CMP0135)
    cmake_policy(SET CMP0135 NEW)
endif()

include(FetchContent)
FetchContent_Declare(
        enet
        URL https://github.com/lsalzman/enet/archive/refs/tags/v1.3.18.tar.gz
)
FetchContent_MakeAvailable(enet)

# Server
add_executable(Server
        src/Server/main.cpp
        src/Server/NetServer.cpp
        src/Server/NetServer.h
        src/Server/Config.h
)
target_include_directories(Server PRIVATE
        "${enet_SOURCE_DIR}/include"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/Server"
)
target_link_libraries(Server PRIVATE enet)

# Client
add_executable(Client
        src/Client/main.cpp
        src/Client/NetClient.cpp
        src/Client/NetClient.h
        src/Client/main.cpp
        src/Client/NetClient.cpp
        src/Client/NetClient.h
)
target_include_directories(Client PRIVATE
        "${enet_SOURCE_DIR}/include"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/Client"
)
target_link_libraries(Client PRIVATE enet)

if(WIN32)
    target_link_libraries(Server PRIVATE ws2_32 winmm)
    target_link_libraries(Client PRIVATE ws2_32 winmm)
endif()