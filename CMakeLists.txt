cmake_minimum_required(VERSION 3.24)
project(OOP_lab)

set(CMAKE_CXX_STANDARD 23)

include_directories(.)
include_directories(controller)
include_directories(domain)
include_directories(repository)
include_directories(test)
include_directories(ui)
include_directories(gui)


set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_executable(OOP_lab
        app.cpp
        controller/Controller.cpp
        controller/Controller.h
        domain/Domain.cpp
        domain/Domain.h
        repository/Repository.cpp
        repository/Repository.h
        ui/Console.cpp
        ui/Console.h
        gui/mainwindow.cpp
        gui/mainwindow.h
        )

target_link_libraries(OOP_lab PRIVATE Qt5::Widgets)


