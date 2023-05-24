cmake_minimum_required(VERSION 3.24)
project(OOP_lab)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(controller)
include_directories(domain)
include_directories(repository)
include_directories(test)
include_directories(ui)

add_executable(OOP_lab
        controller/Controller.cpp
        controller/Controller.h
        domain/Domain.cpp
        domain/Domain.h
        repository/Repository.cpp
        repository/Repository.h
        test/Test.cpp
        test/Test.h
        ui/Console.cpp
        ui/Console.h
        app.cpp)
