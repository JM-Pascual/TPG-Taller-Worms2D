cmake_minimum_required(VERSION 3.0)

project(worms2d VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -pedantic -pedantic-errors -O0 -ggdb -DDEBUG -fno-inline -D _POSIX_C_SOURCE=200809L")

set(TARGET_DIR ../target)

file(GLOB COMMON_SRC common/*.cpp)
file(GLOB CLIENT_SRC client/*.cpp client/main.cpp)
file(GLOB SERVER_SRC server/*.cpp server/main.cpp)


# add_library(common_objects SHARED ${COMMON_SRC})

add_executable(client_exe ${COMMON_SRC} ${CLIENT_SRC})

add_executable(server_exe ${COMMON_SRC} ${SERVER_SRC})

set_target_properties(client_exe server_exe PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${TARGET_DIR})
set_target_properties(client_exe PROPERTIES OUTPUT_NAME worms2d)
set_target_properties(server_exe PROPERTIES OUTPUT_NAME worms2dsv)