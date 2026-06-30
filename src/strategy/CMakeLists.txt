project(strategy)

file(GLOB STRATEGY_SRC_LISTS  ${CMAKE_CURRENT_SOURCE_DIR}/*.c ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp )

#生成库
add_library(${PROJECT_NAME}
SHARED
${STRATEGY_SRC_LISTS}
)

# 添加库头文件路径
target_include_directories(${PROJECT_NAME}
    PUBLIC
    ${Map_Dir}
) 

# 添加库链接
target_link_libraries(${PROJECT_NAME}
    PUBLIC
    grid_map
)

