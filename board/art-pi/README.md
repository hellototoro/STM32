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
- [ ] LCD
- [ ] WiFi & BLE
