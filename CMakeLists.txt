cmake_minimum_required(VERSION 3.0)

project(worms2d VERSION 0.0.1)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_mixer 2.6.3 REQUIRED)
find_package(SDL2pp REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS})
include_directories(${SDL2_IMAGE_INCLUDE_DIRS})
include_directories(${SDL2_MIXER_INCLUDE_DIRS})
include_directories(${SDL2PP_INCLUDE_DIRS})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -pedantic -pedantic-errors -O0 -ggdb -DDEBUG -fno-inline -D _POSIX_C_SOURCE=200809L")

set(TARGET_DIR ../target)

add_definitions(-DDATA_PATH="${PROJECT_SOURCE_DIR}/sprites")
include_directories(${SDL2PP_INCLUDE_DIRS})

file(GLOB COMMON_SRC common/*.cpp)
file(GLOB CLIENT_SRC client/*.cpp client/main.cpp)
file(GLOB SERVER_SRC server/*.cpp server/main.cpp)


add_executable(client_exe ${COMMON_SRC} ${CLIENT_SRC})

target_include_directories(client_exe PUBLIC ${SDL2_INCLUDE_DIRS})
target_include_directories(client_exe PUBLIC ${SDL2_IMAGE_INCLUDE_DIRS})
target_include_directories(client_exe PUBLIC ${SDL2_MIXER_INCLUDE_DIRS})

target_link_libraries(client_exe PUBLIC SDL2pp::SDL2pp)
target_link_libraries(client_exe PUBLIC SDL2)
target_link_libraries(client_exe PUBLIC SDL2_image)
target_link_libraries(client_exe PUBLIC SDL2_mixer)
target_link_libraries(client_exe PUBLIC ${SDL2PP_LIBRARIES})


add_executable(server_exe ${COMMON_SRC} ${SERVER_SRC})

set_target_properties(client_exe server_exe PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${TARGET_DIR})
set_target_properties(client_exe PROPERTIES OUTPUT_NAME worms2d)
set_target_properties(server_exe PROPERTIES OUTPUT_NAME worms2dsv)