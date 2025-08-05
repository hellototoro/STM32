#ifndef LVGL_PORT_H
#define LVGL_PORT_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 * GLOBAL PROTOTYPES
 **********************/

void lvgl_port_init(void);
void read_tp_data(void);

/**********************
 *      MACROS
 **********************/
#define LV_USE_INDEV_TOUCH 0

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /*LVGL_PORT_H*/
