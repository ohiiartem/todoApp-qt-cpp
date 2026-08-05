cmake_minimum_required(VERSION 3.21)
project(TodoApp LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets Core)

qt_add_executable(ToDoApp
    main.cpp
    mainwindow.cpp
    taskmanager.cpp
    mainwindow.h
    taskmanager.h
    resources.qrc
    AppStateMachine.h AppStateMachine.cpp
    task.h
    task.cpp
)

target_link_libraries(ToDoApp PRIVATE Qt6::Widgets Qt6::Core)
