cmake_minimum_required(VERSION 3.16)
project(ISS_Tracker VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD 17)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets Network)

file(COPY img/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_executable(ISS_Tracker
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
)

target_link_libraries(ISS_Tracker PRIVATE
    Qt6::Core
    Qt6::Widgets
    Qt6::Network
)
