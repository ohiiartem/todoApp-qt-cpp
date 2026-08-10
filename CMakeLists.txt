cmake_minimum_required(VERSION 3.21)
project(TodoApp LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets Core)

#----Core logic----

qt_add_library(todoapp_core STATIC
    taskmanager.h     taskmanager.cpp
    AppStateMachine.h AppStateMachine.cpp
    task.h            task.cpp
)
target_include_directories(todoapp_core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(todoapp_core PUBLIC Qt::Core)

#----Application

qt_add_executable(ToDoApp
    main.cpp
    mainwindow.h mainwindow.cpp
    resources.qrc
)
target_link_libraries(ToDoApp PRIVATE todoapp_core Qt6::Widgets)

#----Tests

option(TODOAPP_BUILD_TESTS "Build unit tests" ON)

if(TODOAPP_BUILD_TESTS)
    include(FetchContent)
    FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.15.2.zip
    )
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)

    enable_testing()

    add_executable(todoapp_tests
        tests/TaskManagerTest.cpp
    )
    target_link_libraries(todoapp_tests PRIVATE todoapp_core GTest::gtest_main)

    include(GoogleTest)
    gtest_discover_tests(todoapp_tests)
endif()
