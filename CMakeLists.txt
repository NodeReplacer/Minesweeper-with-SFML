cmake_minimum_required(VERSION 3.23)
project(Minesweeper)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_EXE_LINKER_FLAGS "-static")
set(SFML_STATIC_LIBRARIES TRUE)

add_executable(Minesweeper main.cpp Game.cpp Game.h)

set(SFML_DIR ${CMAKE_CURRENT_SOURCE_DIR}/SFML/lib/cmake/SFML)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/SFML/include)
find_package(SFML COMPONENTS system window graphics audio network REQUIRED)

target_link_libraries(Minesweeper sfml-system sfml-window sfml-graphics sfml-audio)