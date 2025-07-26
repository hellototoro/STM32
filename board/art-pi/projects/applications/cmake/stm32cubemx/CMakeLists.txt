cmake_minimum_required(VERSION 3.22)
# Enable CMake support for ASM and C languages
enable_language(C ASM)
# STM32CubeMX generated symbols (macros)
set(MX_Defines_Syms 
	USE_PWR_LDO_SUPPLY 
	USE_HAL_DRIVER 
	STM32H750xx
    $<$<CONFIG:Debug>:DEBUG>
)

# STM32CubeMX generated include paths
set(MX_Include_Dirs
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Core/Inc
    ${CMAKE_CURRENT_SOURCE_DIR}/../../FATFS/Target
    ${CMAKE_CURRENT_SOURCE_DIR}/../../FATFS/App
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Drivers/STM32H7xx_HAL_Driver/Inc
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/FreeRTOS/Source/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/FatFs/src
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Drivers/CMSIS/Device/ST/STM32H7xx/Include
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Drivers/CMSIS/Include
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/lwip-network-interface-integration/include/
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/lwip-network-interface-integration/source/
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/lwip-freertos-integration/
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/wifi-host-driver/
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/wifi-host-driver/COMPONENT_WIFI5/inc/
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/wifi-host-driver/COMPONENT_WIFI5/src/
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/wifi-host-driver/COMPONENT_WIFI5/src/include/
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/wifi-host-driver/COMPONENT_WIFI5/resources/resource_imp/
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/wifi-host-driver/COMPONENT_WIFI5/src/bus_protocols/
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/wifi-connection-manager/include/
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/connectivity-utilities/
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/connectivity-utilities/cy_log/
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/connectivity-utilities/JSON_parser/
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/connectivity-utilities/linked_list/
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/connectivity-utilities/cy_string/
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/connectivity-utilities/network/
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/whd-bsp-integration/
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/LwIP/src/include/
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/whd-bsp-integration
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/LwIP/src/include/compat/posix/arpa
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/LwIP/src/include/compat/posix/net
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/LwIP/src/include/compat/posix
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/LwIP/src/include/compat/posix/sys
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/LwIP/src/include/compat/stdc
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/LwIP/src/include/lwip
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/LwIP/src/include/lwip/apps
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/LwIP/src/include/lwip/priv
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/LwIP/src/include/lwip/prot
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/pal/core-lib/include/
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/pal/hal/include/
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/pal/common/Inc/
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/pal/targets/TARGET_STM32/Inc/
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/wifi-connection-manager/source/COMPONENT_43438/
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/pal/abstraction-rtos/include/
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/pal/abstraction-rtos/source/COMPONENT_FREERTOS/
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/pal/abstraction-rtos/include/COMPONENT_FREERTOS/
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/pal/hal/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/pal/common/Inc
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/pal/targets/TARGET_STM32/Inc
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/pal/core-lib/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/wifi-connection-manager/source/COMPONENT_43438
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/wifi-host-driver/COMPONENT_WIFI5/inc
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/wifi-host-driver/COMPONENT_WIFI5/resources/resource_imp
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/pal/abstraction-rtos/include
)

# STM32CubeMX generated application sources
set(MX_Application_Src
    ${CMAKE_CURRENT_SOURCE_DIR}/../../FATFS/App/fatfs.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../FATFS/Target/bsp_driver_sd.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../FATFS/Target/sd_diskio.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../FATFS/Target/fatfs_platform.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Core/Src/main.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Core/Src/gpio.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Core/Src/freertos.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Core/Src/crc.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Core/Src/dcmi.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Core/Src/dma.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Core/Src/dma2d.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Core/Src/eth.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Core/Src/fdcan.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Core/Src/fmc.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Core/Src/i2c.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Core/Src/ltdc.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Core/Src/sdmmc.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Core/Src/spi.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Core/Src/tim.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Core/Src/usart.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Core/Src/usb_otg.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Core/Src/stm32h7xx_it.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Core/Src/stm32h7xx_hal_msp.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Core/Src/stm32h7xx_hal_timebase_tim.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Core/Src/sysmem.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Core/Src/syscalls.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../startup_stm32h750xx.s
)

# STM32 HAL/LL Drivers
set(STM32_Drivers_Src
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Core/Src/system_stm32h7xx.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_tim.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_tim_ex.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_cortex.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_crc.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_crc_ex.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_rcc.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_rcc_ex.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_flash.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_flash_ex.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_gpio.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_hsem.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_dma.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_dma_ex.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_mdma.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_pwr.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_pwr_ex.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_i2c.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_i2c_ex.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_exti.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_dcmi.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_dma2d.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_eth.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_eth_ex.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_fdcan.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_ll_fmc.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_nor.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_sram.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_nand.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_sdram.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_ltdc.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_ltdc_ex.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_dsi.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_ll_sdmmc.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_ll_delayblock.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_sd.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_sd_ex.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_mmc.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_mmc_ex.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_spi.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_spi_ex.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_uart.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_uart_ex.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_pcd.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_pcd_ex.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_ll_usb.c
)

# Drivers Midllewares


set(FreeRTOS_Src
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/FreeRTOS/Source/croutine.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/FreeRTOS/Source/event_groups.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/FreeRTOS/Source/list.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/FreeRTOS/Source/queue.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/FreeRTOS/Source/stream_buffer.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/FreeRTOS/Source/tasks.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/FreeRTOS/Source/timers.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/cmsis_os2.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/FreeRTOS/Source/portable/MemMang/heap_4.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F/port.c
)
set(Connectivity_Src
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/pal/abstraction-rtos/source/COMPONENT_FREERTOS/cyabs_freertos_helpers.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/pal/abstraction-rtos/source/COMPONENT_FREERTOS/cyabs_rtos_freertos.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/pal/abstraction-rtos/source/COMPONENT_FREERTOS/cyabs_freertos_common.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/pal/abstraction-rtos/source/cy_worker_thread.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/btstack-integration/COMPONENT_HCI-UART/firmware/COMPONENT_43438/COMPONENT_AW-CU427-P/w_bt_firmware_controller.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/pal/common/Src/cyhal_system.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/pal/common/Src/wifi_bt_if.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/pal/targets/TARGET_STM32/Src/stm32_cyhal_gpio.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/pal/targets/TARGET_STM32/Src/stm32_cyhal_lptimer.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/pal/targets/TARGET_STM32/Src/stm32_cyhal_sdio.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/pal/targets/TARGET_STM32/Src/stm32_cyhal_spi.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/pal/targets/TARGET_STM32/Src/stm32_cyhal_trng.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/pal/targets/TARGET_STM32/Src/stm32_cyhal_uart.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/pal/targets/TARGET_STM32/Src/stm32_cyhal_syspm.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/LwIP/src/api/api_lib.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/LwIP/src/api/api_msg.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/LwIP/src/api/err.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/LwIP/src/api/if_api.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/LwIP/src/api/netbuf.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/LwIP/src/api/netdb.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/LwIP/src/api/netifapi.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/LwIP/src/api/sockets.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/LwIP/src/api/tcpip.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/LwIP/src/core/altcp.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/LwIP/src/core/altcp_alloc.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/LwIP/src/core/altcp_tcp.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/LwIP/src/core/def.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/LwIP/src/core/dns.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/LwIP/src/core/inet_chksum.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/LwIP/src/core/init.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/LwIP/src/core/ip.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/LwIP/src/core/ipv4/autoip.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/LwIP/src/core/ipv4/dhcp.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/LwIP/src/core/ipv4/etharp.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/LwIP/src/core/ipv4/icmp.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/LwIP/src/core/ipv4/igmp.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/LwIP/src/core/ipv4/ip4.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/LwIP/src/core/ipv4/ip4_addr.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/LwIP/src/core/ipv4/ip4_frag.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/LwIP/src/core/ipv6/dhcp6.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/LwIP/src/core/ipv6/ethip6.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/LwIP/src/core/ipv6/icmp6.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/LwIP/src/core/ipv6/inet6.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/LwIP/src/core/ipv6/ip6.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/LwIP/src/core/ipv6/ip6_addr.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/LwIP/src/core/ipv6/ip6_frag.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/LwIP/src/core/ipv6/mld6.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/LwIP/src/core/ipv6/nd6.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/LwIP/src/core/mem.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/LwIP/src/core/memp.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/LwIP/src/core/netif.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/LwIP/src/core/pbuf.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/LwIP/src/core/raw.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/LwIP/src/core/stats.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/LwIP/src/core/sys.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/LwIP/src/core/tcp.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/LwIP/src/core/tcp_in.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/LwIP/src/core/tcp_out.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/LwIP/src/core/timeouts.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/LwIP/src/core/udp.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/LwIP/src/netif/ethernet.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/whd-bsp-integration/cybsp_wifi.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/whd-bsp-integration/COMPONENT_LWIP/cy_network_buffer_lwip.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/connectivity-utilities/cy_log/cy_log.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/connectivity-utilities/JSON_parser/cy_json_parser.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/connectivity-utilities/linked_list/cy_linked_list.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/connectivity-utilities/cy_string/cy_string_utils.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/connectivity-utilities/network/cy_nw_helper_common.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/connectivity-utilities/network/COMPONENT_LWIP/cy_nw_helper.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/wifi-connection-manager/source/cy_wcm.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/wifi-host-driver/COMPONENT_WIFI5/src/bus_protocols/whd_bus.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/wifi-host-driver/COMPONENT_WIFI5/src/bus_protocols/whd_bus_common.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/wifi-host-driver/COMPONENT_WIFI5/src/bus_protocols/whd_bus_sdio_protocol.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/wifi-host-driver/COMPONENT_WIFI5/src/bus_protocols/whd_bus_spi_protocol.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/wifi-host-driver/COMPONENT_WIFI5/src/bus_protocols/whd_bus_emusbh_impl.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/wifi-host-driver/COMPONENT_WIFI5/src/bus_protocols/whd_bus_usb_protocol.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/wifi-host-driver/COMPONENT_WIFI5/src/whd_ap.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/wifi-host-driver/COMPONENT_WIFI5/src/whd_buffer_api.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/wifi-host-driver/COMPONENT_WIFI5/src/whd_cdc_bdc.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/wifi-host-driver/COMPONENT_WIFI5/src/whd_chip.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/wifi-host-driver/COMPONENT_WIFI5/src/whd_chip_constants.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/wifi-host-driver/COMPONENT_WIFI5/src/whd_clm.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/wifi-host-driver/COMPONENT_WIFI5/src/whd_debug.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/wifi-host-driver/COMPONENT_WIFI5/src/whd_events.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/wifi-host-driver/COMPONENT_WIFI5/src/whd_logging.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/wifi-host-driver/COMPONENT_WIFI5/src/whd_management.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/wifi-host-driver/COMPONENT_WIFI5/src/whd_network_if.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/wifi-host-driver/COMPONENT_WIFI5/src/whd_proto.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/wifi-host-driver/COMPONENT_WIFI5/src/whd_resource_if.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/wifi-host-driver/COMPONENT_WIFI5/src/whd_sdpcm.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/wifi-host-driver/COMPONENT_WIFI5/src/whd_thread.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/wifi-host-driver/COMPONENT_WIFI5/src/whd_utils.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/wifi-host-driver/COMPONENT_WIFI5/src/whd_wifi.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/wifi-host-driver/COMPONENT_WIFI5/src/whd_wifi_api.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/wifi-host-driver/COMPONENT_WIFI5/src/whd_wifi_p2p.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/wifi-host-driver/COMPONENT_WIFI5/src/whd_commonring.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/wifi-host-driver/COMPONENT_WIFI5/src/whd_flowring.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/wifi-host-driver/COMPONENT_WIFI5/src/whd_ring.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/wifi-host-driver/COMPONENT_WIFI5/resources/resource_imp/whd_resources.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/lwip-network-interface-integration/source/cy_ethernetif.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/lwip-network-interface-integration/source/cy_lwip_dhcp_server.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/lwip-network-interface-integration/source/cy_network_mw_core.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/lwip-freertos-integration/arch/sys_arch.c
)
set(FatFs_Src
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/FatFs/src/diskio.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/FatFs/src/ff.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/FatFs/src/ff_gen_drv.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/FatFs/src/option/syscall.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/FatFs/src/option/ccsbcs.c
)

# Link directories setup
set(MX_LINK_DIRS

)
# Project static libraries
set(MX_LINK_LIBS 
    STM32_Drivers
    ${TOOLCHAIN_LINK_LIBRARIES}
    FreeRTOS	Connectivity	FatFs	
)
# Interface library for includes and symbols
add_library(stm32cubemx INTERFACE)
target_include_directories(stm32cubemx INTERFACE ${MX_Include_Dirs})
target_compile_definitions(stm32cubemx INTERFACE ${MX_Defines_Syms})

# Create STM32_Drivers static library
add_library(STM32_Drivers OBJECT)
target_sources(STM32_Drivers PRIVATE ${STM32_Drivers_Src})
target_link_libraries(STM32_Drivers PUBLIC stm32cubemx)


# Create FreeRTOS static library
add_library(FreeRTOS OBJECT)
target_sources(FreeRTOS PRIVATE ${FreeRTOS_Src})
target_link_libraries(FreeRTOS PUBLIC stm32cubemx)

# Create Connectivity static library
add_library(Connectivity OBJECT)
target_sources(Connectivity PRIVATE ${Connectivity_Src})
target_link_libraries(Connectivity PUBLIC stm32cubemx)

# Create FatFs static library
add_library(FatFs OBJECT)
target_sources(FatFs PRIVATE ${FatFs_Src})
target_link_libraries(FatFs PUBLIC stm32cubemx)

# Add STM32CubeMX generated application sources to the project
target_sources(${CMAKE_PROJECT_NAME} PRIVATE ${MX_Application_Src})

# Link directories setup
target_link_directories(${CMAKE_PROJECT_NAME} PRIVATE ${MX_LINK_DIRS})

# Add libraries to the project
target_link_libraries(${CMAKE_PROJECT_NAME} ${MX_LINK_LIBS})

# Add the map file to the list of files to be removed with 'clean' target
set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES ADDITIONAL_CLEAN_FILES ${CMAKE_PROJECT_NAME}.map)

# Validate that STM32CubeMX code is compatible with C standard
if((CMAKE_C_STANDARD EQUAL 90) OR (CMAKE_C_STANDARD EQUAL 99))
    message(ERROR "Generated code requires C11 or higher")
endif()
