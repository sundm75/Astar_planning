project(Astar_main)

add_subdirectory(grid_map)
add_subdirectory(strategy)

add_executable(${PROJECT_NAME} main.cpp)


# easyx库
# 头文件路径
target_include_directories(${PROJECT_NAME} 
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/map 
    ${CMAKE_CURRENT_SOURCE_DIR}/strategy    
)

# 添加库文件
target_link_libraries(${PROJECT_NAME} 
    PUBLIC
    strategy
)

# 添加头文件路径
target_include_directories(${PROJECT_NAME}
    PUBLIC
    ${CMAKE_SOURCE_DIR}/third_party/easyx/include
)  

# 添加库路径
target_link_directories(${PROJECT_NAME}
    PUBLIC
    ${CMAKE_SOURCE_DIR}/third_party/easyx/lib64
)
# 添加库
target_link_libraries(${PROJECT_NAME}
    PUBLIC
    easyx
)
