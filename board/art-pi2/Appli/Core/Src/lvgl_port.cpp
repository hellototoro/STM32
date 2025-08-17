/*********************
 *      INCLUDES
 *********************/

#include "lvgl_port.h"
#include "lvgl.h"
#include "main.h"

#define LV_USE_INDEV_TOUCH 0

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

#define LV_DOUBLE_BUFFER 0

/**********************
 *   GLOBAL FUNCTIONS
 **********************/
#if defined(__ARMCC_VERSION)
uint8_t lvgl_fb1[MY_DISP_HOR_RES * MY_DISP_VER_RES * 2] __attribute__((aligned(32)));
#else
// extern uint8_t lvgl_fb1;
uint8_t lvgl_fb1[MY_DISP_HOR_RES * MY_DISP_VER_RES * 2];
extern uint8_t lvgl_fb2;
#endif

void lvgl_port_init(void) {
  lv_init();

  lv_tick_set_cb(HAL_GetTick);

#if defined(__ARMCC_VERSION)
  uint8_t *fb1 = (uint8_t *)lvgl_fb1;
  uint8_t *fb2 = NULL;
#else
  uint8_t *fb1 = (uint8_t *)lvgl_fb1;
  uint8_t *fb2 = NULL;
#if LV_DOUBLE_BUFFER
  fb2 = (uint8_t *)&lvgl_fb2;
#endif /* LV_DOUBLE_BUFFER */
#endif /* __ARMCC_VERSION */

  lv_st_ltdc_create_direct((void *)fb1, (void *)fb2, 0);

#if LV_USE_INDEV_TOUCH
  touchPad.init();
  lv_indev_t *indev = lv_indev_create();
  lv_indev_set_type(indev, LV_INDEV_TYPE_POINTER);
  lv_indev_set_read_cb(indev, lvgl_touchscreen_read);
#endif
}

uint8_t *lvgl_get_fb(uint8_t layerIndex) {
  if (layerIndex == 0) {
    return lvgl_fb1;
  }
  return NULL;
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
