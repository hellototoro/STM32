app1_flash_origin = 0x90000000
app1_flash_length = 1024K /* 1MB of application flash memory */
app1_flash_end = app1_flash_origin + app1_flash_length;

wifi_flash_origin = app1_flash_end
wifi_flash_length = 512K /* 512KB of WiFi flash memory */
wifi_flash_end = wifi_flash_origin + wifi_flash_length;

MEMORY
{
    WIFI_FLASH (rx)   : ORIGIN = wifi_flash_origin, LENGTH = wifi_flash_length /* 512KB of WiFi Flash memory */
}

SECTIONS
{
    .whd_fw :
    {
        . = ALIGN(4);
        __whd_fw_start = .; /* Start of WHD firmware section */
        KEEP(*(.whd_fw)) /* Keep the WHD firmware section */
        __whd_fw_end = .; /* End of WHD firmware section */
        . = ALIGN(4);
    } >WIFI_FLASH
}
