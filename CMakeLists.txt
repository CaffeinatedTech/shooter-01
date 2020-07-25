cmake_minimum_required(VERSION 3.16)
project(shooter)

set(CMAKE_CXX_STANDARD 20)

add_executable(shooter src/main.cpp src/engine.cpp headers/engine.h src/player.cpp headers/player.h src/input.cpp src/draw.cpp headers/textureholder.h src/textureholder.cpp src/update.cpp headers/bullet.h src/bullet.cpp src/Enemy.cpp headers/Enemy.h src/Explosion.cpp headers/Explosion.h)

include_directories(headers /usr/include)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML REQUIRED system window graphics network audio)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(shooter ${SFML_LIBRARIES})
endif()

file(COPY graphics DESTINATION ${CMAKE_BINARY_DIR})