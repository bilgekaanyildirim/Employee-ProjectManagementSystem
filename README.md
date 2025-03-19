# Employee-Project Management System

This project is a **C++ implementation** of an **employee-project management system** using a **two-dimensional hybrid linked list (2DHLL)** and a **stack-based undo system**. It allows users to assign employees to projects, withdraw them, print assigned projects, and undo actions.

## Features
- Uses a **hybrid linked list (2DHLL)** to store employee-project relationships.
- Assigns employees to projects with **priority-based sorting**.
- Supports **undo functionality** using a stack-based structure.
- Prints employee-project relationships in **ascending order**.
- Ensures **memory safety** by deallocating dynamically allocated memory.

## Files
- `main.cpp` → The main program that controls user interactions.
- `EmployeeProject2DLL.h` → Header file defining the **2DHLL structure**.
- `EmployeeProject2DLL.cpp` → Implementation of **employee-project operations**.
- `UndoStack.h` → Header file for the **undo stack**.
- `UndoStack.cpp` → Implementation of **undo operations**.
