/**
  ******************************************************************************
  * @file    mt25tl01g_conf_template.h
  * @author  MCD Application Team
  * @brief   This file contains all the description of the
  *          W25QXX QSPI memory.
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef W25QXX_CONF_H
#define W25QXX_CONF_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32h7xx.h"
#include "stm32h7xx_hal.h"

/** @addtogroup BSP
  * @{
  */
#define CONF_QSPI_DUMMY_CLOCK                 8U

/* Dummy cycles for STR read mode */
#define W25QXX_DUMMY_CYCLES_READ_QUAD      8U
#define W25QXX_DUMMY_CYCLES_READ           8U
/* Dummy cycles for DTR read mode */
#define W25QXX_DUMMY_CYCLES_READ_DTR       6U
#define W25QXX_DUMMY_CYCLES_READ_QUAD_DTR  6U

#ifdef __cplusplus
}
#endif

#endif /* W25QXX_CONF_H */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

