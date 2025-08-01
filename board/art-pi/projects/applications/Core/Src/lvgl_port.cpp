/*********************
 *      INCLUDES
 *********************/

#include "lvgl_port.h"
#include "cmsis_os2.h"
#include "lvgl.h"
#include "main.h"
#include <cstddef>
#include <stdio.h>

#define LV_USE_INDEV_TOUCH 1

#if LV_USE_INDEV_TOUCH
#include "Ft5xx6.hpp"
#endif

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/

#if LV_USE_INDEV_TOUCH
static void lvgl_touchscreen_read(lv_indev_t *indev, lv_indev_data_t *data);
Ft5xx6 touchPad(I2C_Handle);
#endif

/**********************
 *  STATIC VARIABLES
 **********************/

#if LV_USE_INDEV_TOUCH
static volatile uint8_t touch_irq = 0;
static volatile int32_t last_x = 0;
static volatile int32_t last_y = 0;
static volatile lv_indev_state_t last_state = LV_INDEV_STATE_RELEASED;
#endif

/**********************
 *      MACROS
 **********************/
#define MY_DISP_HOR_RES 320
#define MY_DISP_VER_RES 480

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

void lvgl_port_init(void) {
  lv_init();

  lv_tick_set_cb(osKernelGetTickCount);

  extern uint32_t lvgl_fb1;
  extern uint32_t lvgl_fb2;

  lv_st_ltdc_create_direct((void *)&lvgl_fb1, (void *)&lvgl_fb2, 0);

#if LV_USE_INDEV_TOUCH
  touchPad.init();
  lv_indev_t *indev = lv_indev_create();
  lv_indev_set_type(indev, LV_INDEV_TYPE_POINTER);
  lv_indev_set_read_cb(indev, lvgl_touchscreen_read);
#endif
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

#if LV_USE_INDEV_TOUCH
static void lvgl_touchscreen_read(lv_indev_t *indev, lv_indev_data_t *data) {
  UNUSED(indev);
  /*Use the saved coordinates if there were an interrupt*/
  uint16_t xRaw, yRaw;
  uint8_t points = touchPad.readData(xRaw, yRaw);
  if (0 < points && points < 6) {
    /* reset interrupt flag */
    data->point.x = yRaw;
    data->point.y = xRaw;
    data->state = LV_INDEV_STATE_PRESSED;
  }
  /*If there is no interrupt the touch is released*/
  else {
    data->state = LV_INDEV_STATE_RELEASED;
  }
}

void read_tp_data(void)
{
}
#endif
