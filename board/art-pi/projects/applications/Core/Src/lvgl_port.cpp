/*********************
 *      INCLUDES
 *********************/

#include "lvgl_port.h"
#include "lvgl.h"
#include "main.h"


#if LV_USE_INDEV_TOUCH
#include "Ft5xx6.hpp"
#endif

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/
#if (LVGL_VERSION_MAJOR < 9)

#define TFT_FULL_REFRESH	0

#if LV_USE_GPU_STM32_DMA2D
__IO uint32_t transferCompleteDetected = 0;  /* DMA2D Transfer Complete flag */
HAL_StatusTypeDef HAL_Status = HAL_OK;
#endif

static void ex_disp_flush(lv_disp_drv_t *drv, const lv_area_t *area, lv_color_t * color_p);
static void ex_disp_clean_dcache(lv_disp_drv_t *drv);

#if LV_USE_GPU_STM32_DMA2D
static void DMA2D_Config(uint32_t xSize);
static void TransferComplete(DMA2D_HandleTypeDef *hdma2d);
static void TransferError(DMA2D_HandleTypeDef *hdma2d);
#endif

static lv_disp_drv_t disp_drv;

#if LV_COLOR_DEPTH == 16
typedef uint16_t uintpixel_t;
#elif LV_COLOR_DEPTH == 24 || LV_COLOR_DEPTH == 32
typedef uint32_t uintpixel_t;
#endif

static lv_disp_t *our_disp = NULL;

#if LV_USE_GPU_STM32_DMA2D
static int32_t            x1_flush;
static int32_t            y1_flush;
static int32_t            x2_flush;
static int32_t            y2_fill;
static int32_t            y_fill_act;
static const lv_color_t * buf_to_flush;
#endif

extern DMA2D_HandleTypeDef hdma2d;

#endif

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
extern uint8_t lvgl_fb1;
extern uint8_t lvgl_fb2;
#endif

void lvgl_port_init(void) {
  lv_init();

#if LVGL_VERSION_MAJOR > 8
  lv_tick_set_cb(HAL_GetTick);

#if defined(__ARMCC_VERSION)
  uint8_t *fb1 = (uint8_t *)lvgl_fb1;
  uint8_t *fb2 = NULL;
#else
  uint8_t *fb1 = (uint8_t *)&lvgl_fb1;
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
#else
   /*-----------------------------
	* Create a buffer for drawing
	*----------------------------*/

   /* LVGL requires a buffer where it draws the objects. The buffer's has to be greater than 1 display row*/

	static lv_disp_draw_buf_t disp_buf_1;
#if TFT_FULL_REFRESH
	static lv_color_t fb[2][MY_DISP_HOR_RES*TFT_VER_RES];
	lv_disp_draw_buf_init(&disp_buf_1, fb[0], fb[1], MY_DISP_HOR_RES * TFT_VER_RES);   /*Initialize the display buffer*/
#else
	static lv_color_t buf[MY_DISP_HOR_RES * 68];
	lv_disp_draw_buf_init(&disp_buf_1, buf, NULL, MY_DISP_HOR_RES * 68);   /*Initialize the display buffer*/
#endif

	/*-----------------------------------
	* Register the display in LittlevGL
	*----------------------------------*/

	lv_disp_drv_init(&disp_drv);                    /*Basic initialization*/

	/*Set up the functions to access to your display*/

	/*Set the resolution of the display*/
	disp_drv.hor_res = MY_DISP_HOR_RES;
	disp_drv.ver_res = MY_DISP_VER_RES;

	/*Used to copy the buffer's content to the display*/
	disp_drv.flush_cb = ex_disp_flush;
	disp_drv.clean_dcache_cb = ex_disp_clean_dcache;
	disp_drv.full_refresh = TFT_FULL_REFRESH;

	/*Set a display buffer*/
	disp_drv.draw_buf = &disp_buf_1;

	/*Finally register the driver*/
	our_disp = lv_disp_drv_register(&disp_drv);
#endif /* LVGL_VERSION_MAJOR > 8 */
}

/**********************
 *   STATIC FUNCTIONS
 **********************/
#if (LVGL_VERSION_MAJOR > 8)
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
#else
static void ex_disp_flush(lv_disp_drv_t *drv, const lv_area_t *area,
                          lv_color_t *color_p) {
  UNUSED(drv);
#if TFT_FULL_REFRESH == 0
  uint8_t *fb1 = (uint8_t *)&lvgl_fb1;

	uint16_t * fb = (uint16_t *) fb1;
	uint16_t stride = disp_drv.hor_res;
	fb += area->y1 * stride;
	fb += area->x1;
	lv_coord_t w = lv_area_get_width(area);
	int32_t y;
	for(y = area->y1; y <= area->y2; y++) {
		lv_memcpy(fb, color_p, w * 2);
		fb += stride;
		color_p += w;
	}
#else
	HAL_LTDC_SetAddress(&hlcd_ltdc, color_p, 0);
#endif
	lv_disp_flush_ready(&disp_drv);
}


static void ex_disp_clean_dcache(lv_disp_drv_t *drv) {
    UNUSED(drv);
    SCB_CleanInvalidateDCache();
}

#if LV_USE_GPU_STM32_DMA2D
/**
  * @brief  DMA2D Transfer completed callback
  * @param  hdma2d: DMA2D handle.
  * @note   This example shows a simple way to report end of DMA2D transfer, and
  *         you can add your own implementation.
  * @retval None
  */
static void TransferComplete(DMA2D_HandleTypeDef *hdma2d)
{
    (void)hdma2d;
	  lv_disp_flush_ready(&disp_drv);
//	transferCompleteDetected = 1;
}

/**
  * @brief  DMA2D error callbacks
  * @param  hdma2d: DMA2D handle
  * @note   This example shows a simple way to report DMA2D transfer error, and you can
  *         add your own implementation.
  * @retval None
  */
static void TransferError(DMA2D_HandleTypeDef *hdma2d)
{
    (void)hdma2d;
}
#endif
#endif
