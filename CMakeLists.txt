cmake_minimum_required(VERSION 3.30)
project(towerdefence)

set(CMAKE_CXX_STANDARD 20)
find_package(SFML 2.6.2 REQUIRED COMPONENTS system window graphics)

add_executable(towerdefence main.cpp Map.cpp)
target_link_libraries(towerdefence sfml-system sfml-window sfml-graphics)

file(COPY ${CMAKE_SOURCE_DIR}/Imagenes DESTINATION ${CMAKE_BINARY_DIR})