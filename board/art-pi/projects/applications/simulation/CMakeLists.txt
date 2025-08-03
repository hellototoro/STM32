cmake_minimum_required(VERSION 3.22)

project(simulation)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 11)
set( CMAKE_C_FLAGS "-Wall -Wextra -Wno-unused -g" )
set( CMAKE_CXX_FLAGS "-Wall -Wextra -Wno-unused -g" )

set(CMAKE_POLICY_DEFAULT_CMP0077 NEW)
set(CMAKE_POLICY_DEFAULT_CMP0126 NEW)
set(CMAKE_POLICY_DEFAULT_CMP0079 NEW) # 允许跨目录链接目标
# cmake_policy(SET CMP0079 NEW) 

# Enable CMake support for ASM, C and C++ languages
enable_language(C CXX ASM)

add_executable(${PROJECT_NAME} main.c)

find_package(SDL2 REQUIRED SDL2)
include_directories(
    ${SDL2_INCLUDE_DIRS}
    ${SDL2_INCLUDE_DIRS}/../
)

set(CONFIG_LV_BUILD_DEMOS OFF)
set(CONFIG_LV_BUILD_EXAMPLES OFF)
set(LV_BUILD_CONF_PATH "${CMAKE_SOURCE_DIR}/lv_conf.h")

add_subdirectory(${CMAKE_SOURCE_DIR}/../lvgl ${BIN_OUTPUT_DIR}/lvgl)
target_link_libraries(lvgl PUBLIC ${SDL2_LIBRARIES})

add_subdirectory(${CMAKE_SOURCE_DIR}/../App ${BIN_OUTPUT_DIR}/App)
target_link_libraries(App INTERFACE lvgl)

target_include_directories(${PROJECT_NAME} PRIVATE
    # Add user defined include paths
    ${CMAKE_SOURCE_DIR}
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    lvgl
    App
)
