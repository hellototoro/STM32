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

.section 是用来定义一个新的段（Section），类似于 C 语言中 .data、.text 等。
.isr_vector：自定义段的名字，通常是链接脚本中指定的中断向量表段名。
"a"：段属性，表示该段是 allocatable，会被加载到目标文件中并最终放入内存。
%progbits：段的内容是程序数据（二进制），而非 BSS（未初始化段）。

指定了栈顶地址和入口函数地址：_estack 和 Reset_Handler。
所以linker script中定义的入口函数 ENTRY(Reset_Handler) 是给链接器和调试器用的，不设置可能导致调试器不知道从哪开始运行程序，它确保 Reset_Handler 一定不会被链接器优化掉（否则启动失败）。

_sidata = LOADADDR(.data); : LOADADDR() 是链接器的一个函数，用于返回 .data 段在 Flash 中的地址。

```ldscript
  PROVIDE( __data_start = ADDR(.data) );
  PROVIDE( __data_size = __data_end - __data_start );
  PROVIDE( __data_source = LOADADDR(.data) );
  PROVIDE( __data_source_end = __tdata_source_end );
  PROVIDE( __data_source_size = __data_source_end - __data_source );
```

```c
// 在启动代码中使用这些符号
extern uint32_t __data_start;
extern uint32_t __data_size;
extern uint32_t __data_source;

// 复制初始化数据从Flash到RAM
void copy_data_section(void) {
    uint32_t *src = &__data_source;
    uint32_t *dst = &__data_start;
    uint32_t size = (uint32_t)&__data_size;
    
    for (uint32_t i = 0; i < size/4; i++) {
        dst[i] = src[i];
    }
}
```


PROVIDE 函数：
PROVIDE用于有条件地定义符号。只有当该符号在链接的目标文件中没有被定义时，才会创建这个符号。
特点
非强制性定义：如果程序代码中已经定义了同名符号，PROVIDE定义的符号会被忽略
默认值提供：为程序提供默认的符号值
向后兼容：确保链接脚本的修改不会破坏现有代码
PROVIDE_HIDDEN与PROVIDE功能相同，但定义的符号是隐藏的，不会被导出到符号表中，只在链接时可见。

ADDR 函数：
ADDR返回指定段（section）的虚拟内存地址（VMA - Virtual Memory Address）。
特点
获取段地址：返回段在内存中的起始地址
运行时地址：返回程序运行时该段所在的地址
与LOADADDR区别：ADDR返回VMA，LOADADDR返回LMA（Load Memory Address）

```ldscript
  PROVIDE( __bss_start = __tbss_start );
  PROVIDE( __bss_size = __bss_end - __bss_start );
```

```c
extern uint32_t __bss_start;
extern uint32_t __bss_size;

void clear_bss_section(void) {
    uint32_t *bss = &__bss_start;
    uint32_t size = (uint32_t)&__bss_size;
    
    for (uint32_t i = 0; i < size/4; i++) {
        bss[i] = 0;
    }
}
```
