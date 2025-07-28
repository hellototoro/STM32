# ART-PI

[ART-PI项目地址](https://art-pi.github.io/website/)

## 项目简介

ART-PI是RT-Thread基于STM32H7系列出品的一款非常优秀的开源硬件，板载资源非常丰富。
本项目是基于FreeRTOS实时系统来驱动板载资源。
尽管RT-Thread非常优秀，但是我们希望尽可能多的适配各种各样的RTOS，所以才有了这个项目。

## 目标

1. 基于FreeRTOS将板载资源驱动起来
2. 在裸板基础上添加camera和lcd
3. 移植LVGL

## TODO List

- [x] bootloader(qspi flash)
- [x] SDRAM
- [x] spi flash
- [x] SD Card
- [x] LCD
- [x] WiFi
- [ ] BLE

## 相关资料链接

1. [MPU配置](https://shequ.stmicroelectronics.cn/thread-641003-1-1.html)
2. [FreeRTOS 中断](https://mcuoneclipse.com/2016/08/28/arm-cortex-m-interrupts-and-freertos-part-3/?utm_source=chatgpt.com)
3. [FreeRTOS 的Task存储在DTCM中1](https://forums.freertos.org/t/freertos-stm32f4-7-task-structs-in-dtcm/6544)
4. [FreeRTOS 的Task存储在DTCM中2](https://forums.freertos.org/t/stack-in-dtcm-on-i-mxrt10xx/9148)
