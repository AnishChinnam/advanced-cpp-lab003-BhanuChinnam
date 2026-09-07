# Lab 003: Advanced C++ Class Design with RAII and Ownership

This assignment is designed to move students beyond trivial getter/setter exercises.
Instead, students implement a small resource-owning C++ class that manages dynamic memory without using std::vector.

## Learning Objectives

- Design and implement a nontrivial class
- Understand constructors and destructors
- Implement copy constructor and copy assignment
- Implement move constructor and move assignment
- Use operator overloading correctly
- Keep member data encapsulated
- Apply const correctness
- Follow RAII and exception safety patterns
- Manage a resource manually using raw pointers safely

## Required Class Responsibilities

Your class should manage a dynamically allocated buffer with:

- default constructor
- parameterized constructor
- destructor
- copy constructor
- copy assignment operator
- move constructor
- move assignment operator
- element access via [] and at()
- resizing support
- comparison operators
- optional explicit conversion to bool

## Challenge

Implement a resource-owning class such as DynamicBuffer or a similar data structure without using std::vector.

This assignment is intentionally more advanced and simulates real-world C++ responsibilities expected in later course work.

## GitHub Classroom Instructions

- Read the TODO comments in the template files.
- Implement the class in src/exercise.cpp.
- Keep code organized and memory-safe.
- Run `make test` to validate your implementation.
- Submit your final version when the class behaves correctly.

## Build Instructions

1. Clone the repository
2. Navigate to the project directory
3. Run `make`
4. Run `make run`
5. Run `make test`
6. Run `make clean` when finished
