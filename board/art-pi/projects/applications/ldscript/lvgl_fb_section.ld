.lvgl_framebuffer (NOLOAD) : ALIGN(32)
{
  _slvgl_framebuffer = lvgl_fb_start;   /* create a global symbol at lvgl framebuffer start */
  . = . + lvgl_fb_size;
  . = . + lvgl_fb_size;
  *(.lvgl_framebuffer*)     /* .lvgl_framebuffer* sections */
} >SDRAM
