# MCU linker script & startup pipeline

This document describes the startup pipeline for the stm mcu.

## Linker script

1. 定义了程序的内存布局，控制着代码和数据段的链接方式、位置和对齐等。

```ldscript
ENTRY(Reset_Handler)

MEMORY
{
  FLASH (rx) : ORIGIN = 0x08000000, LENGTH = 512K
  RAM   (rwx) : ORIGIN = 0x20000000, LENGTH = 128K
}

SECTIONS
{
  .text : 
  {
    KEEP(*(.isr_vector))      /* 中断向量表 */
    *(.text*)                 /* 所有代码段 */
    *(.rodata*)               /* 只读数据 */
    KEEP(*(.init)) KEEP(*(.fini))
  } > FLASH

  .ARM.extab : { *(.ARM.extab* .gnu.linkonce.armextab.*) } > FLASH
  .ARM.exidx : { *(.ARM.exidx* .gnu.linkonce.armexidx.*) } > FLASH

  .data : 
  {
    _sdata = .;
    *(.data*)
    _edata = .;
  } > RAM AT > FLASH

  .bss :
  {
    _sbss = .;
    *(.bss*)
    *(COMMON)
    _ebss = .;
  } > RAM

  . = ALIGN(4);
  _end = .;
}
```

链接脚本的输入是多个编译后的中间目标文件（.o 文件）及库文件，输出是一个可执行文件（.elf）、可下载映像文件（.bin / .hex）等。链接脚本定义了输出文件的内存布局和段内容来源。

这些目标文件中包含了多个段（sections），例如：
.text：代码段
.rodata：只读数据
.data：初始化全局变量
.bss：未初始化全局变量
自定义段，如 .isr_vector, .boot, .heap

链接器根据链接脚本：

分析输入文件中各个段的内容；
根据 SECTIONS { ... } 的定义，将输入段映射到输出段；
将各段的地址排布在 MEMORY 区域中；
对变量/函数地址进行重定位；
根据 ENTRY() 指定的入口函数，设置程序入口点；
生成最终输出文件。

相关语法：
定义段的 NOLOAD 属性，表示该段不参与链接，只用于描述内存布局。

## startup.s

```armasm
.section  .isr_vector,"a",%progbits
.type  g_pfnVectors, %object


g_pfnVectors:
  .word  _estack
  .word  Reset_Handler

  .word  NMI_Handler
```

指定了栈顶地址和入口函数地址：_estack 和 Reset_Handler。
所以linker script中定义的入口函数 ENTRY(Reset_Handler) 是给链接器和调试器用的，不设置可能导致调试器不知道从哪开始运行程序，它确保 Reset_Handler 一定不会被链接器优化掉（否则启动失败）。
