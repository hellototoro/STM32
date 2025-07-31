lvgl_fb_start = ORIGIN(SDRAM);
lvgl_fb_size  = 320 * 480 * 2; /* 320x480 RGB565 framebuffer size */
lvgl_fb_end = lvgl_fb_start + lvgl_fb_size * 2; /* Double buffer */

PROVIDE(lvgl_fb1 = lvgl_fb_start); /* Provide a global symbol at lvgl framebuffer start */
PROVIDE(lvgl_fb2 = lvgl_fb_start + lvgl_fb_size); /* Provide a global symbol at lvgl framebuffer end */
