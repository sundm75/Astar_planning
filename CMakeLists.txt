cmake_minimum_required(VERSION 3.10)
project (AstarPlanning)

set(CMAKE_CXX_STANDARD 17)

# 变量设置 
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(Map_Dir ${CMAKE_SOURCE_DIR}/src/grid_map)
set(Strategy_Dir ${CMAKE_SOURCE_DIR}/src/strategy)

#添加子目录
add_subdirectory(src)

