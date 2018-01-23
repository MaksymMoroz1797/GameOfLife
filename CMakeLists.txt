cmake_minimum_required(VERSION 3.9)
project(GameOfLife_1)

set(CMAKE_CXX_STANDARD 11)

add_executable(GameOfLife_1 main.cpp Field/Field.h Field/Field.cpp Field/FieldBuilder.h Field/FieldBuilder.cpp Game/Game.h Game/Game.cpp ThreadPool/ThreadPool.h ThreadPool/ThreadPool.cpp)