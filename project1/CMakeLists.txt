cmake_minimum_required(VERSION 3.10)
project(MemoryPool)

include_directories(include tests)

find_package(fmt REQUIRED)
add_executable(MemoryPool main.cpp)

target_link_libraries(MemoryPool PRIVATE fmt::fmt)