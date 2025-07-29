/*********************
 *      INCLUDES
 *********************/

#include "lvgl_port.h"
#include "cmsis_os2.h"
#include "lvgl.h"
#include "main.h"
#include "print.h"

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

#if 1
  static __attribute__((
      aligned(32))) uint8_t buf_direct_2[MY_DISP_HOR_RES * MY_DISP_VER_RES * 2];
  lv_st_ltdc_create_direct((void *)SDRAM_BANK_ADDR, buf_direct_2, 0);
#else
  static __attribute__((aligned(32))) uint8_t buf_partial_1[800 * 480];
  static __attribute__((aligned(32))) uint8_t buf_partial_2[800 * 480];
  lv_st_ltdc_create_partial(buf_partial_1, buf_partial_2, 800 * 480, 0);
#endif

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
  /*Use the saved coordinates if there were an interrupt*/
  if (touch_irq) {
    /* reset interrupt flag */
    touch_irq = 0;
    data->point.x = last_x;
    data->point.y = last_y;
    data->state = last_state;
  }
  /*If there is no interrupt the touch is released*/
  else {
    last_state = LV_INDEV_STATE_RELEASED;
  }
}

void read_tp_data(void)
{
  touch_irq = 1;
  uint16_t xRaw, yRaw;
  uint8_t points = touchPad.readData(xRaw, yRaw);
  if (0 < points && points < 6) {
    last_y = xRaw;
    last_x = yRaw;
    last_state = LV_INDEV_STATE_PRESSED;
    // printf("x = %ld, y = %ld\r\n", last_x, last_y);
  } else {
    last_state = LV_INDEV_STATE_RELEASED;
  }
}
#endif
