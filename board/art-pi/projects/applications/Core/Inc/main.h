/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32h7xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define SDRAM_BANK_ADDR (0xC0000000UL)
#define SD_CARD_DETECT_Pin GPIO_PIN_5
#define SD_CARD_DETECT_GPIO_Port GPIOD
#define TP_RST_Pin GPIO_PIN_3
#define TP_RST_GPIO_Port GPIOD
#define LED_RED_Pin GPIO_PIN_15
#define LED_RED_GPIO_Port GPIOC
#define TP_IRQ_Pin GPIO_PIN_12
#define TP_IRQ_GPIO_Port GPIOG
#define WIFI_HOST_WAKE_Pin GPIO_PIN_3
#define WIFI_HOST_WAKE_GPIO_Port GPIOE
#define WIFI_REG_ON_Pin GPIO_PIN_13
#define WIFI_REG_ON_GPIO_Port GPIOC
#define LED_BLUE_Pin GPIO_PIN_8
#define LED_BLUE_GPIO_Port GPIOI
#define BT_WAKE_Pin GPIO_PIN_10
#define BT_WAKE_GPIO_Port GPIOI
#define BT_RST_N_Pin GPIO_PIN_11
#define BT_RST_N_GPIO_Port GPIOI
#define BT_HOST_WAKE_Pin GPIO_PIN_0
#define BT_HOST_WAKE_GPIO_Port GPIOC
#define LCD_CS_Pin GPIO_PIN_3
#define LCD_CS_GPIO_Port GPIOH
#define LCD_MOSI_Pin GPIO_PIN_2
#define LCD_MOSI_GPIO_Port GPIOB
#define CAM_RESET_Pin GPIO_PIN_3
#define CAM_RESET_GPIO_Port GPIOA
#define LCD_SCK_Pin GPIO_PIN_0
#define LCD_SCK_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
