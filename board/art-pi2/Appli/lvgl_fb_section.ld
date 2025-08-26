.lvgl_framebuffer (NOLOAD) : ALIGN(32)
{
  _slvgl_framebuffer = lvgl_fb_start;   /* create a global symbol at lvgl framebuffer start */
  . = . + lvgl_fb_size;
  /* . = . + lvgl_fb_size; */
  *(.lvgl_framebuffer*)     /* .lvgl_framebuffer* sections */
} >RAM

.lvgl_framebuffer2 (NOLOAD) : ALIGN(32)
{
  _slvgl_framebuffer2 = lvgl_fb2_start;   /* create a global symbol at lvgl framebuffer start */
  . = . + lvgl_fb_size;
  /* . = . + lvgl_fb_size; */
  *(.lvgl_framebuffer2*)     /* .lvgl_framebuffer2* sections */
} >EXTRAM
