cmake_minimum_required(VERSION 3.27)
project(Employee-ProjectManagementSystemUsingAHybridDataStructure)

set(CMAKE_CXX_STANDARD 17)

add_executable(Employee-ProjectManagementSystemUsingAHybridDataStructure main.cpp
        EmployeeProject2DLL.cpp
        EmployeeProject2DLL.h
        UndoStack.cpp
        UndoStack.h)
