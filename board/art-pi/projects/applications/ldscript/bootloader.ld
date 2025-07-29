internal_flash_size = 128K; /* 128K internal flash */
internal_flash_start = 0x08000000;
internal_flash_end = internal_flash_start + internal_flash_size;

boot_flash_size = 32K;
boot_flash_start = internal_flash_start;
boot_flash_end = boot_flash_start + boot_flash_size;

meta_flash_size = 32K;
meta_flash_start = boot_flash_end;
meta_flash_end = meta_flash_start + meta_flash_size;

/*
MEMORY
{
  FLASH_BOOT (rx)   : ORIGIN = boot_flash_start,  LENGTH = boot_flash_size
  FLASH_META (rx)   : ORIGIN = meta_flash_start,  LENGTH = meta_flash_size
} 
*/
