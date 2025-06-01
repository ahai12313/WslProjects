cmake_minimum_required(VERSION 3.14)  # 升级到更现代的版本
project(DesignPattern LANGUAGES CXX)

# 设置 C++ 标准（根据项目需要调整）
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# 定义可执行文件
add_executable(DesignPattern main.cpp)

# 优先通过 CONFIG 模式查找 fmt
find_package(fmt CONFIG REQUIRED)

# 为特定目标添加头文件路径
target_include_directories(DesignPattern
    PRIVATE
        include
        tests
)

# 链接依赖库
target_link_libraries(DesignPattern PRIVATE fmt::fmt)

# 可选：启用地址消毒等调试选项
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_options(DesignPattern PRIVATE 
        -Wall 
        -Wextra
        -g
        # -fsanitize=address
        -fsanitize=undefined
    )
    target_link_options(DesignPattern PRIVATE 
        # -fsanitize=address
        -fsanitize=undefined
    )
endif()