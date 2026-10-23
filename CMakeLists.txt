cmake_minimum_required(VERSION 3.16)
project(UndoRedoTextEditor LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_executable(UndoRedoTextEditor main.cpp)
target_link_libraries(UndoRedoTextEditor PRIVATE Qt6::Widgets)
