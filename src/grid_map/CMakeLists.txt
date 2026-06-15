project(grid_map)

file(GLOB GRID_MAP_SRC_LISTS  ${CMAKE_CURRENT_SOURCE_DIR}/*.c ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp )

add_library(${PROJECT_NAME}
SHARED
${GRID_MAP_SRC_LISTS}
)

# easyx库
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