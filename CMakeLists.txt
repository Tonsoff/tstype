cmake_minimum_required(VERSION 3.16)
project(tstype)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_AUTOMOC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_executable(tstype
    main.cpp
)

target_link_libraries(tstype Qt6::Widgets)
