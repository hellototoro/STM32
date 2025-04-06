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
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

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

# Core project settings
project(${CMAKE_PROJECT_NAME})
message("Build type: " ${CMAKE_BUILD_TYPE})

# Enable CMake support for ASM, C and C++ languages
enable_language(C CXX ASM)

# Create an executable object type
add_executable(${CMAKE_PROJECT_NAME})

# Add STM32CubeMX generated sources
add_subdirectory(cmake/stm32cubemx)

# 向子模块 Connectivity 传递 symbols 和头文件目录以及源文件
set(COMPONENT_43438_DIR ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/wifi-host-driver/COMPONENT_WIFI5/resources)

target_compile_definitions(Connectivity PRIVATE
    # Enable using CY_HAL for rtos-abstraction
    CY_USING_HAL=1
    CYBSP_WIFI_CAPABLE=1
)

target_include_directories(Connectivity PRIVATE
    ${COMPONENT_43438_DIR}/firmware/COMPONENT_43438/
    ${COMPONENT_43438_DIR}/clm/COMPONENT_43438/
    ${COMPONENT_43438_DIR}/nvram/COMPONENT_43438/COMPONENT_AW-CU427-P/
)

target_sources(Connectivity PRIVATE
    ${COMPONENT_43438_DIR}/firmware/COMPONENT_43438/43438A1_bin.c
    ${COMPONENT_43438_DIR}/firmware/COMPONENT_43438/43438A1-mfgtest_bin.c
    ${COMPONENT_43438_DIR}/clm/COMPONENT_43438/43438A1-mfgtest_clm_blob.c
    ${COMPONENT_43438_DIR}/clm/COMPONENT_43438/43438A1_clm_blob.c
)

# Add touchgfx generated sources and libraries
add_subdirectory(cmake/touchgfx)

# Link directories setup
target_link_directories(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined library search paths
)

# Add sources to executable
target_sources(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user sources here
    Bsp/Components/ili9481/ili9481.c
    Bsp/Components/st7789/st7789.c
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
    Core/Src/wifi_task.c
)

# Add include paths
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined include paths
    Bsp/Components/ili9481
    Bsp/Components/st7789
    Bsp/Components/sdram
    Bsp/Components/sdcard
    Bsp/Components/ft5xx6
    Bsp/Components/w25qxx
    MyDrivers/hw_iic
    MyDrivers/print
    Middlewares/Third_Party/FreeRTOS/FreeRTOS-Plus/Source/FreeRTOS-Plus-CLI
    FreeRTOS_CLI
)

# Add project symbols (macros)
target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined symbols
    USE_FULL_ASSERT
)

# Add linked libraries
target_link_libraries(${CMAKE_PROJECT_NAME}
    stm32cubemx

    # Add user defined libraries
)
