# application

## 内存布局


![H7 的系统架构](res/STM32H7_SystemArchitecture.png)

sram_d1 : 300k(320 * 480 * 2) for lvgl framebuffer

## lvgl 配置说明

1. LV_ST_LTDC_USE_DMA2D_FLUSH 选项：
无论是否启用 OS，可以使用 DMA2D 并行地刷新部分缓冲区，与其他 LVGL 任务一起。如果显示不是部分显示，则无需启用此选项。
LV_ST_LTDC_USE_DMA2D_FLUSH 不能与 LV_USE_DRAW_DMA2D 同时启用。请参阅 DMA2D 支持。
LV_USE_DRAW_DMA2D 适用于配备了 NeoChrom GPU 的 STM32 mcu
