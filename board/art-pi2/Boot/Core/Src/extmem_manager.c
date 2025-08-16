/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : extmem_manager.c
  * @version        : 1.0.0
  * @brief          : This file implements the extmem configuration
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "extmem_manager.h"
#include <string.h>

/* USER CODE BEGIN Includes */
#include "main.h"
#include "w35t51nwtbie.h"

/* USER CODE END Includes */

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/

/* USER CODE END PV */

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/

/* USER CODE END PFP */

/*
 * -- Insert your variables declaration here --
 */
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/*
 * -- Insert your external function declaration here --
 */
/* USER CODE BEGIN 1 */
static void MX_XSPI2_Init(void) {

  /* USER CODE BEGIN XSPI2_Init 0 */

  /* USER CODE END XSPI2_Init 0 */

  XSPIM_CfgTypeDef sXspiManagerCfg = {0};

  /* USER CODE BEGIN XSPI2_Init 1 */

  /* USER CODE END XSPI2_Init 1 */
  /* XSPI2 parameter configuration*/
  hxspi2.Instance = XSPI2;
  hxspi2.Init.FifoThresholdByte = 4;
  hxspi2.Init.MemoryMode = HAL_XSPI_SINGLE_MEM;
  hxspi2.Init.MemoryType = HAL_XSPI_MEMTYPE_MICRON;
  hxspi2.Init.MemorySize = HAL_XSPI_SIZE_512MB;
  hxspi2.Init.ChipSelectHighTimeCycle = 2;
  hxspi2.Init.FreeRunningClock = HAL_XSPI_FREERUNCLK_DISABLE;
  hxspi2.Init.ClockMode = HAL_XSPI_CLOCK_MODE_0;
  hxspi2.Init.WrapSize = HAL_XSPI_WRAP_NOT_SUPPORTED;
  hxspi2.Init.ClockPrescaler = 0;
  hxspi2.Init.SampleShifting = HAL_XSPI_SAMPLE_SHIFT_NONE;
  hxspi2.Init.DelayHoldQuarterCycle = HAL_XSPI_DHQC_ENABLE;
  hxspi2.Init.ChipSelectBoundary = HAL_XSPI_BONDARYOF_NONE;
  hxspi2.Init.MaxTran = 0;
  hxspi2.Init.Refresh = 0;
  hxspi2.Init.MemorySelect = HAL_XSPI_CSSEL_NCS1;
  if (HAL_XSPI_Init(&hxspi2) != HAL_OK) {
    Error_Handler();
  }
  sXspiManagerCfg.nCSOverride = HAL_XSPI_CSSEL_OVR_NCS1;
  sXspiManagerCfg.IOPort = HAL_XSPIM_IOPORT_2;
  if (HAL_XSPIM_Config(&hxspi2, &sXspiManagerCfg,
                       HAL_XSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK) {
    Error_Handler();
  }
  /* USER CODE BEGIN XSPI2_Init 2 */

  /* USER CODE END XSPI2_Init 2 */
}

int32_t EXTMEM_Flash_Probe(void) {
  uint8_t device_id[3];
  int retr = 0;

  if (W35T51NWTBIE_OK != W35T51NWTBIE_ReadID(&hxspi2, W35T51NWTBIE_SPI_MODE,
                                             W35T51NWTBIE_STR_TRANSFER,
                                             device_id,
                                             W35T51NWTBIE_3BYTES_SIZE)) {
    EXTMEM_MACRO_DEBUG("Read Flash ID Fail\n");
    return -1;
  } else {
    EXTMEM_MACRO_DEBUG("Read Flash ID success:0x%.2x 0x%.2x 0x%.2x\n",
                       device_id[0], device_id[1], device_id[2]);

    /* stage 1. enter octal mode and set flash register max speed and other
     * configs */
    retr = W35T51NWTBIE_EnterOctal_DTR_Mode(&hxspi2);
    if (retr != W35T51NWTBIE_OK) {
      EXTMEM_MACRO_DEBUG("Flash Enter Octal mode Fail, errno:%d\n", retr);
      return -1;
    }

    if (HAL_XSPI_DeInit(&hxspi2) != HAL_OK) {
      EXTMEM_MACRO_DEBUG("Flash deinit error");
      return -1;
    }

    /* stage 2. reinit and use new configs to achieve maxim speed */
    EXTMEM_MACRO_DEBUG("Reconfigure Flash clock\n");
    MX_XSPI2_Init();

    if (W35T51NWTBIE_OK != W35T51NWTBIE_ReadID(&hxspi2, W35T51NWTBIE_OPI_MODE,
                                               W35T51NWTBIE_DTR_TRANSFER,
                                               device_id,
                                               W35T51NWTBIE_4BYTES_SIZE)) {
      EXTMEM_MACRO_DEBUG("Flash Re-Enter octal failed\n");
      return -1;
    } else {
      EXTMEM_MACRO_DEBUG(
          "Flash Re-Enter Octal DTR and Read ID success:%.2x %.2x %.2x\n",
          device_id[0], device_id[1], device_id[2]);
      return 0;
    }
  }
}

int32_t EXTMEM_Flash_EnterXIP(void) {
  if (W35T51NWTBIE_OK !=
      W35T51NWTBIE_EnableMemoryMappedModeDTR(&hxspi2, W35T51NWTBIE_SPI_MODE)) {
    EXTMEM_MACRO_DEBUG("Flash XIP failed\n");
    return -1;
  } else {
    EXTMEM_MACRO_DEBUG("Flash XIP success\n");
    return 0;
  }
}

/* USER CODE END 1 */

/**
  * Init External memory manager
  * @retval None
  */
void MX_EXTMEM_MANAGER_Init(void)
{

  /* USER CODE BEGIN MX_EXTMEM_Init_PreTreatment */
  memset(extmem_list_config, 0x0, sizeof(extmem_list_config));
  extmem_list_config[0].MemType = EXTMEM_NOR_SFDP;
  extmem_list_config[0].Handle = (void *)&hxspi2;
  extmem_list_config[0].ConfigType = EXTMEM_LINK_CONFIG_8LINES;
  EXTMEM_Flash_Probe();
  EXTMEM_Flash_EnterXIP();
  return;

  /* USER CODE END MX_EXTMEM_Init_PreTreatment */
  HAL_RCCEx_EnableClockProtection(RCC_CLOCKPROTECT_XSPI);

  /* Initialization of the memory parameters */
  memset(extmem_list_config, 0x0, sizeof(extmem_list_config));

  /* EXTMEMORY_1 */
  extmem_list_config[0].MemType = EXTMEM_NOR_SFDP;
  extmem_list_config[0].Handle = (void*)&hxspi2;
  extmem_list_config[0].ConfigType = EXTMEM_LINK_CONFIG_8LINES;

  EXTMEM_Init(EXTMEMORY_1, HAL_RCCEx_GetPeriphCLKFreq(RCC_PERIPHCLK_XSPI2));

  /* USER CODE BEGIN MX_EXTMEM_Init_PostTreatment */

  /* USER CODE END MX_EXTMEM_Init_PostTreatment */
}
