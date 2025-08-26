lvgl_fb_start = ORIGIN(RAM);
lvgl_fb2_start = ORIGIN(EXTRAM);
lvgl_fb_size  = 320 * 480 * 2; /* 320x480 RGB565 framebuffer size */

PROVIDE(lvgl_fb1 = lvgl_fb_start); /* Provide a global symbol at lvgl framebuffer start */
PROVIDE(lvgl_fb2 = lvgl_fb2_start); /* Provide a global symbol at lvgl framebuffer end */
