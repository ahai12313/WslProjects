cmake_minimum_required(VERSION 3.14)  # 升级到更现代的版本
project(Model LANGUAGES CXX)

# 设置 C++ 标准（根据项目需要调整）
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# 定义可执行文件
add_executable(Model main.cpp)

# 优先通过 CONFIG 模式查找 fmt
find_package(fmt CONFIG REQUIRED)

# 为特定目标添加头文件路径
target_include_directories(Model
    PRIVATE
        include
        tests
)

# 链接依赖库
target_link_libraries(Model PRIVATE fmt::fmt)

# 可选：启用地址消毒等调试选项
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_options(Model PRIVATE 
        -Wall 
        -Wextra
        -g
        # -fsanitize=address
        -fsanitize=undefined
    )
    target_link_options(Model PRIVATE 
        # -fsanitize=address
        -fsanitize=undefined
    )
endif()