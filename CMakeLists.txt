cmake_minimum_required(VERSION 3.7)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_definitions(-std=c++17)

set(CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS, "${CXX_FLAGS}")

project(SDL2Test)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

#https://stackoverflow.com/questions/28651088/how-to-use-cmakes-pkg-search-module-when-compiling-under-windows
find_package(SDL2 REQUIRED)
INCLUDE(FindPkgConfig)
PKG_SEARCH_MODULE(SDL2TTF REQUIRED SDL2_ttf)
include_directories(${SDL2_INCLUDE_DIRS} src)
include_directories(${SDL2_TTF_INCLUDE_DIR} src)

add_executable(SnakeGame src/main.cpp src/game.cpp src/controller.cpp src/renderer.cpp src/snake.cpp src/LeaderBoard.cpp src/MapTile.cpp src/MapLoader.cpp)
string(STRIP ${SDL2_LIBRARIES} SDL2_LIBRARIES)
target_link_libraries(SnakeGame ${SDL2_LIBRARIES} ${SDL2TTF_LIBRARIES} ${SDL2_IMAGE_LIBRARY})
