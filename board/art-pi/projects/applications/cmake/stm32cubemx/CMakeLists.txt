cmake_minimum_required(VERSION 3.22)

project(stm32cubemx)
add_library(stm32cubemx INTERFACE)

# Enable CMake support for ASM, C and C++ languages
enable_language(C CXX ASM)

target_compile_definitions(stm32cubemx INTERFACE 
	USE_HAL_DRIVER 
	STM32H750xx
    $<$<CONFIG:Debug>:DEBUG>
)

target_include_directories(stm32cubemx INTERFACE
    ../../Core/Inc
    ../../FATFS/Target
    ../../FATFS/App
    ../../TouchGFX/App
    ../../TouchGFX/target/generated
    ../../TouchGFX/target
    ../../Drivers/STM32H7xx_HAL_Driver/Inc
    ../../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy
    ../../Middlewares/Third_Party/FreeRTOS/Source/include
    ../../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2
    ../../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F
    ../../Middlewares/Third_Party/FatFs/src
    ../../Drivers/CMSIS/Device/ST/STM32H7xx/Include
    ../../Drivers/CMSIS/Include
)

target_sources(stm32cubemx INTERFACE
    ../../Core/Src/main.c
    ../../Core/Src/gpio.c
    ../../Core/Src/freertos.c
    ../../Core/Src/crc.c
    ../../Core/Src/dcmi.c
    ../../Core/Src/dma.c
    ../../Core/Src/dma2d.c
    ../../Core/Src/eth.c
    ../../Core/Src/fdcan.c
    ../../Core/Src/fmc.c
    ../../Core/Src/i2c.c
    ../../Core/Src/ltdc.c
    ../../Core/Src/memorymap.c
    ../../Core/Src/sdmmc.c
    ../../Core/Src/spi.c
    ../../Core/Src/tim.c
    ../../Core/Src/usart.c
    ../../Core/Src/usb_otg.c
    ../../Core/Src/stm32h7xx_it.c
    ../../Core/Src/stm32h7xx_hal_msp.c
    ../../Core/Src/stm32h7xx_hal_timebase_tim.c
    ../../FATFS/Target/bsp_driver_sd.c
    ../../FATFS/Target/sd_diskio.c
    ../../FATFS/Target/fatfs_platform.c
    ../../FATFS/App/fatfs.c
    ../../TouchGFX/target/TouchGFXHAL.cpp
    ../../TouchGFX/target/STM32TouchController.cpp
    ../../TouchGFX/target/TouchGFXGPIO.cpp
    ../../TouchGFX/target/generated/TouchGFXConfiguration.cpp
    ../../TouchGFX/target/generated/TouchGFXGeneratedHAL.cpp
    ../../TouchGFX/target/generated/STM32DMA.cpp
    ../../TouchGFX/target/generated/OSWrappers.cpp
    ../../TouchGFX/App/app_touchgfx.c
    ../../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_cortex.c
    ../../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_crc.c
    ../../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_crc_ex.c
    ../../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_rcc.c
    ../../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_rcc_ex.c
    ../../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_flash.c
    ../../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_flash_ex.c
    ../../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_gpio.c
    ../../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_hsem.c
    ../../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_dma.c
    ../../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_dma_ex.c
    ../../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_mdma.c
    ../../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_pwr.c
    ../../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_pwr_ex.c
    ../../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal.c
    ../../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_i2c.c
    ../../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_i2c_ex.c
    ../../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_exti.c
    ../../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_dcmi.c
    ../../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_dma2d.c
    ../../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_eth.c
    ../../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_eth_ex.c
    ../../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_fdcan.c
    ../../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_ll_fmc.c
    ../../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_sdram.c
    ../../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_ltdc.c
    ../../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_ltdc_ex.c
    ../../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_dsi.c
    ../../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_ll_sdmmc.c
    ../../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_ll_delayblock.c
    ../../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_sd.c
    ../../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_sd_ex.c
    ../../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_spi.c
    ../../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_spi_ex.c
    ../../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_tim.c
    ../../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_tim_ex.c
    ../../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_uart.c
    ../../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_uart_ex.c
    ../../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_pcd.c
    ../../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_pcd_ex.c
    ../../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_ll_usb.c
    ../../Core/Src/system_stm32h7xx.c
    ../../Middlewares/Third_Party/FatFs/src/diskio.c
    ../../Middlewares/Third_Party/FatFs/src/ff.c
    ../../Middlewares/Third_Party/FatFs/src/ff_gen_drv.c
    ../../Middlewares/Third_Party/FatFs/src/option/syscall.c
    ../../Middlewares/Third_Party/FatFs/src/option/ccsbcs.c
    ../../Middlewares/Third_Party/FreeRTOS/Source/croutine.c
    ../../Middlewares/Third_Party/FreeRTOS/Source/event_groups.c
    ../../Middlewares/Third_Party/FreeRTOS/Source/list.c
    ../../Middlewares/Third_Party/FreeRTOS/Source/queue.c
    ../../Middlewares/Third_Party/FreeRTOS/Source/stream_buffer.c
    ../../Middlewares/Third_Party/FreeRTOS/Source/tasks.c
    ../../Middlewares/Third_Party/FreeRTOS/Source/timers.c
    ../../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/cmsis_os2.c
    ../../Middlewares/Third_Party/FreeRTOS/Source/portable/MemMang/heap_4.c
    ../../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F/port.c
    ../../Core/Src/sysmem.c
    ../../Core/Src/syscalls.c
    ../../startup_stm32h750xx.s
)

target_link_directories(stm32cubemx INTERFACE
)

target_link_libraries(stm32cubemx INTERFACE
)

# Validate that STM32CubeMX code is compatible with C standard
if(CMAKE_C_STANDARD LESS 11)
    message(ERROR "Generated code requires C11 or higher")
endif()

# Validate that STM32CubeMX code is compatible with C++ standard
if(CMAKE_CXX_STANDARD LESS 11)
    message(ERROR "Generated code requires C++11 or higher")
endif()
