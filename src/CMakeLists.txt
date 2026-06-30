project(Astar_main)

add_subdirectory(grid_map)
add_subdirectory(strategy)

#生成可执行文件
add_executable(${PROJECT_NAME} main.cpp)

# easyx库
# 添加头文件路径
target_include_directories(${PROJECT_NAME}
    PUBLIC
    ${CMAKE_SOURCE_DIR}/third_party/easyx/include
) 

# 添加库链接
target_link_directories(${PROJECT_NAME}
    PUBLIC
    ${CMAKE_SOURCE_DIR}/third_party/easyx/lib64
)

# 添加库链接
target_link_libraries(${PROJECT_NAME}
    PUBLIC
    easyx
)

# strategy 库
# 头文件路径
target_include_directories(${PROJECT_NAME} 
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/grid_map 
    ${CMAKE_CURRENT_SOURCE_DIR}/strategy    
)
# 添加库链接
target_link_libraries(${PROJECT_NAME} 
    PUBLIC
    strategy
) 
