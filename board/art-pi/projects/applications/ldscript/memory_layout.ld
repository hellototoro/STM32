
/* Specify the memory areas */
MEMORY
{
  ITCMRAM (xrw)   : ORIGIN = 0x00000000, LENGTH = 64K   /* 64Kb of ITCM RAM */

  /* DTCM RAM used to main heap/stack and rtos heap */
  DTCMRAM (xrw)   : ORIGIN = 0x20000000, LENGTH = 128K

  /* SRAM1 in domain 1 is default ram */
  RAM_D1 (xrw)    : ORIGIN = 0x24000000, LENGTH = 512K  /* 512Kb of SRAM1 in domain 1*/
  RAM1_D2 (xrw)   : ORIGIN = 0x30000000, LENGTH = 128K  /* 128Kb of SRAM1 in domain 2*/
  RAM2_D2 (xrw)   : ORIGIN = 0x30020000, LENGTH = 128K  /* 128Kb of SRAM2 in domain 2*/

  /* SRAM3 in domain 2 is used for ethernet descriptors */
  RAM3_D2 (xrw)   : ORIGIN = 0x30040000, LENGTH = 32K   /* 32Kb of SRAM3 in domain 2*/
  RAM4_D3 (xrw)   : ORIGIN = 0x38000000, LENGTH = 64K   /* 64Kb SRAM4 in domain 3*/
  RAMB_D3 (xrw)   : ORIGIN = 0x38800000, LENGTH = 4K    /* 4Kb of backup SRAM in domain 3, aka RTC RAM */

  /* QSPI Flash memory */
  QFLASH (rx)     : ORIGIN = 0x90000000, LENGTH = 8M /* 8MB of QSPI Flash memory */

  /* External SDRAM used to lvgl framebuffer */
  SDRAM (xrw)     : ORIGIN = 0xC0000000, LENGTH = 32M /* 32Mb of SDRAM */
}
