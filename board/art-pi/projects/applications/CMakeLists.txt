cmake_minimum_required(VERSION 3.22)

#
# This file is generated only once,
# and is not re-generated if converter is called multiple times.
#
# User is free to modify the file as much as necessary
#

# Setup compiler settings
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)


# Define the build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()

# Set the project name
set(CMAKE_PROJECT_NAME applications)

# Include toolchain file
include("cmake/gcc-arm-none-eabi.cmake")

# Enable compile command to ease indexing with e.g. clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

# Enable CMake support for ASM and C languages
enable_language(C CXX ASM)

# Core project settings
project(${CMAKE_PROJECT_NAME})
message("Build type: " ${CMAKE_BUILD_TYPE})

# Create an executable object type
add_executable(${CMAKE_PROJECT_NAME})

# Add STM32CubeMX generated sources
add_subdirectory(cmake/stm32cubemx)

# Link directories setup
target_link_directories(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined library search paths
)

# Root TouchGFX folder - depends on where CMakeLists.txt is located
set(root_tgfx_dir TouchGFX)

# Setup all necessary include directories
# These are used by compiler to search for C or C++ headers
set(touchgfx_include_DIRS

    # Application includes
    ${root_tgfx_dir}/gui/include
    ${root_tgfx_dir}/generated/gui_generated/include
    ${root_tgfx_dir}/generated/images/include
    ${root_tgfx_dir}/generated/bitmaps/include
    ${root_tgfx_dir}/generated/fonts/include
    ${root_tgfx_dir}/generated/texts/include
    ${root_tgfx_dir}/generated/videos/include

    # When running simulator but project started as STM32 project
    ${root_tgfx_dir}/../Middlewares/ST/touchgfx/framework/include
    ${root_tgfx_dir}/../Middlewares/ST/touchgfx/framework/include/common
    ${root_tgfx_dir}/../Middlewares/ST/touchgfx/framework/common/include
)

# Search all source files in to be part of the build
# Use the GLOB to scan everything in the gui and generated folders
# These are essential for generic TouchGFX build
file(GLOB_RECURSE graphics_core_generated_SRCS
    ${root_tgfx_dir}/generated/*.cpp
    ${root_tgfx_dir}/gui/*.cpp
    ${root_tgfx_dir}/gui/*.c
)

set(graphics_core_generated_SRCS ${graphics_core_generated_SRCS})

list(FILTER graphics_core_generated_SRCS EXCLUDE REGEX ".*/simulator/.*")
list(FILTER touchgfx_include_DIRS EXCLUDE REGEX ".*/simulator/.*")

# Add sources to executable
target_sources(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user sources here
    Bsp/Components/ili9481/Ili9481.c
    Bsp/Components/sdram/sdram.c
    Bsp/Components/sdcard/sdcard_test.c
    Bsp/Components/ft5xx6/Ft5xx6.cpp
    Bsp/Components/w25qxx/w25qxx.c
    MyDrivers/hw_iic/hw_iic.cpp
    MyDrivers/print/print.c
    Middlewares/Third_Party/FreeRTOS/FreeRTOS-Plus/Source/FreeRTOS-Plus-CLI/FreeRTOS_CLI.c
    FreeRTOS_CLI/app_cli.c
    FreeRTOS_CLI/cli_commands.c
    # FreeRTOS_CLI/serial.c
    ${graphics_core_generated_SRCS}
)

# Add include paths
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined include paths
    Bsp/Components/ili9481
    Bsp/Components/sdram
    Bsp/Components/sdcard
    Bsp/Components/ft5xx6
    Bsp/Components/w25qxx
    MyDrivers/hw_iic
    MyDrivers/print
    Middlewares/Third_Party/FreeRTOS/FreeRTOS-Plus/Source/FreeRTOS-Plus-CLI
    FreeRTOS_CLI
    ${touchgfx_include_DIRS}
)

# Add project symbols (macros)
target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined symbols
    USE_FULL_ASSERT
)

# Add linked libraries
target_link_libraries(${CMAKE_PROJECT_NAME}
    stm32cubemx
    ${CMAKE_SOURCE_DIR}/Middlewares/ST/touchgfx/lib/core/cortex_m7/gcc/libtouchgfx-float-abi-hard.a

    # Add user defined libraries
)
