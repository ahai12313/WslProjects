cmake_minimum_required(VERSION 3.10)
project(SmartPointer)

include_directories(include tests)

find_package(fmt REQUIRED)
add_executable(SmartPointer main.cpp)

target_link_libraries(SmartPointer PRIVATE fmt::fmt)