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
#include "stm32_extmem_conf.h"
#include "w35t51nwtbie.h"
#include "aps256xx.h"

/* USER CODE END Includes */

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/
XSPI_HSCalTypeDef cal = {0};

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

int32_t EXTMEM_PSRAM_Probe(void)
{
    uint8_t reg[2];

    if (APS256XX_OK != APS256XX_Reset(&hxspi1))
    {
        printf("PSRAM Reset error\n");
        return -1;
    }
    HAL_Delay(20);

    if (APS256XX_OK == APS256XX_ReadReg(&hxspi1, APS256XX_MR0_ADDRESS, reg, 5))
    {
        printf("PSRAM MR0: 0x%.2x, MR1: 0x%.2x\n", reg[0], reg[1]);
    }

    MODIFY_REG(reg[0], ((uint8_t)APS256XX_MR0_LATENCY_TYPE | (uint8_t)APS256XX_MR0_READ_LATENCY_CODE | (uint8_t)APS256XX_MR0_DRIVE_STRENGTH),
               ((uint8_t)APS256XX_MR0_LATENCY_TYPE_FIXED |
                (uint8_t)APS256XX_MR0_RLC_7 |
                (uint8_t)APS256XX_MR0_DS_FULL));
    if (APS256XX_OK == APS256XX_WriteReg(&hxspi1, APS256XX_MR0_ADDRESS, reg[0]))
    {
        printf("PSRAM MR0 SET\n");
    }

    MODIFY_REG(reg[0], (uint8_t)(APS256XX_MR4_WRITE_LATENCY_CODE | APS256XX_MR4_RF_RATE | APS256XX_MR4_PASR),
               ((uint8_t)APS256XX_MR4_WLC_7 |
                APS256XX_MR4_RF_4X |
                APS256XX_MR4_PASR_FULL));
    if (APS256XX_OK == APS256XX_WriteReg(&hxspi1, APS256XX_MR4_ADDRESS, reg[0]))
    {
        printf("PSRAM MR4 SET\n");
    }
    reg[0] = 0;
    MODIFY_REG(reg[0], ((uint8_t)APS256XX_MR8_X8_X16 | (uint8_t)APS256XX_MR8_RBX | (uint8_t)APS256XX_MR8_BT | (uint8_t)APS256XX_MR8_BL),
               ((uint8_t)APS256XX_MR8_X16 |
                (uint8_t)APS256XX_MR8_HYBRID_NONE_BURST_WRAP |
                (uint8_t)APS256XX_MR8_RBX_NOT_SUPPORT |
                (uint8_t)APS256XX_MR8_BL_16_BYTES));
    // reg[0] = 0x40;
    if (APS256XX_OK == APS256XX_WriteReg(&hxspi1, APS256XX_MR8_ADDRESS, reg[0]))
    {
        printf("PSRAM MR8 SET\n");
    }

    HAL_XSPI_GetDelayValue(&hxspi1, &cal);
    printf("cal delay: 0x%.2x, fine: 0x%.2x, coarse 0x%.2x, max 0x%.2x\n", cal.DelayValueType, cal.FineCalibrationUnit, cal.CoarseCalibrationUnit, cal.MaxCalibration);

    if (APS256XX_OK == APS256XX_ReadReg(&hxspi1, APS256XX_MR0_ADDRESS, reg, 7))
    {
        printf("PSRAM MR0: 0x%.2x, MR1: 0x%.2x\n", reg[0], reg[1]);
    }
    if (APS256XX_OK == APS256XX_ReadReg(&hxspi1, APS256XX_MR4_ADDRESS, reg, 7))
    {
        printf("PSRAM MR4: 0x%.2x, MR5: 0x%.2x\n", reg[0], reg[1]);
    }
    if (APS256XX_OK == APS256XX_ReadReg(&hxspi1, APS256XX_MR8_ADDRESS, reg, 7))
    {
        printf("PSRAM MR8: 0x%.2x, MR1: 0x%.2x\n", reg[0], reg[1]);
    }

    HAL_XSPI_GetDelayValue(&hxspi1, &cal);
    printf("cal delay: 0x%.2x, fine: 0x%.2x, coarse 0x%.2x, max 0x%.2x\n", cal.DelayValueType, cal.FineCalibrationUnit, cal.CoarseCalibrationUnit, cal.MaxCalibration);
    return 0;
}

int32_t EXTMEM_PSRAM_EnterXIP(void)
{
    uint32_t ReadLatencyVal = 7;
    uint32_t WriteLatencyVal = 7;

    /*Configure Memory Mapped mode*/
    if (APS256XX_OK != APS256XX_EnableMemoryMappedMode(&hxspi1, ReadLatencyVal, WriteLatencyVal, HAL_XSPI_DATA_16_LINES, 0)) // Liner Burst
    {
        printf("PSRAM XIP Fail\n");
        return -1;
    }
    else
    {
        printf("PSRAM XIP Success\n");
        return 0;
    }
}

void print_xspi_reg(const XSPI_TypeDef *xspi) {
    printf("                XSPI Configuration start\n");
    printf("                XSPI Instance: %p\n", xspi);
    printf("                CR     = 0x%08X\n", xspi->CR);
    printf("                DCR1   = 0x%08X\n", xspi->DCR1);
    printf("                DCR2   = 0x%08X\n", xspi->DCR2);
    printf("                DCR3   = 0x%08X\n", xspi->DCR3);
    printf("                DCR4   = 0x%08X\n", xspi->DCR4);
    printf("                SR     = 0x%08X\n", xspi->SR);
    printf("                FCR    = 0x%08X\n", xspi->FCR);
    printf("                DLR    = 0x%08X\n", xspi->DLR);
    printf("                AR     = 0x%08X\n", xspi->AR);
    printf("                DR     = 0x%08X\n", xspi->DR);
    printf("                PSMKR  = 0x%08X\n", xspi->PSMKR);
    printf("                PSMAR  = 0x%08X\n", xspi->PSMAR);
    printf("                PIR    = 0x%08X\n", xspi->PIR);
    printf("                CCR    = 0x%08X\n", xspi->CCR);
    printf("                TCR    = 0x%08X\n", xspi->TCR);
    printf("                IR     = 0x%08X\n", xspi->IR);
    printf("                ABR    = 0x%08X\n", xspi->ABR);
    printf("                LPTR   = 0x%08X\n", xspi->LPTR);
    printf("                WPCCR  = 0x%08X\n", xspi->WPCCR);
    printf("                WPTCR  = 0x%08X\n", xspi->WPTCR);
    printf("                WPIR   = 0x%08X\n", xspi->WPIR);
    printf("                WPABR  = 0x%08X\n", xspi->WPABR);
    printf("                WCCR   = 0x%08X\n", xspi->WCCR);
    printf("                WTCR   = 0x%08X\n", xspi->WTCR);
    printf("                WIR    = 0x%08X\n", xspi->WIR);
    printf("                WABR   = 0x%08X\n", xspi->WABR);
    printf("                HLCR   = 0x%08X\n", xspi->HLCR);
    printf("                CALFCR = 0x%08X\n", xspi->CALFCR);
    printf("                CALMR  = 0x%08X\n", xspi->CALMR);
    printf("                CALSOR = 0x%08X\n", xspi->CALSOR);
    printf("                CALSIR = 0x%08X\n", xspi->CALSIR);
    printf("                XSPI Configuration end\n\n\n");
}
/* USER CODE END 1 */

/**
  * Init External memory manager
  * @retval None
  */
void MX_EXTMEM_MANAGER_Init(void)
{

  /* USER CODE BEGIN MX_EXTMEM_Init_PreTreatment */

  /* USER CODE END MX_EXTMEM_Init_PreTreatment */
  HAL_RCCEx_EnableClockProtection(RCC_CLOCKPROTECT_XSPI);

  /* Initialization of the memory parameters */
  memset(extmem_list_config, 0x0, sizeof(extmem_list_config));

  /* EXTMEMORY_1 */
  extmem_list_config[0].MemType = EXTMEM_NOR_SFDP;
  extmem_list_config[0].Handle = (void*)&hxspi2;
  extmem_list_config[0].ConfigType = EXTMEM_LINK_CONFIG_8LINES;

  /* EXTMEMORY_2 */
  extmem_list_config[1].MemType = EXTMEM_PSRAM;
  extmem_list_config[1].Handle = (void*)&hxspi1;
  extmem_list_config[1].ConfigType = EXTMEM_LINK_CONFIG_16LINES;

  extmem_list_config[1].PsramObject.psram_public.MemorySize = HAL_XSPI_SIZE_256MB;
  extmem_list_config[1].PsramObject.psram_public.FreqMax = 200 * 1000000u;
  extmem_list_config[1].PsramObject.psram_public.NumberOfConfig = 1u;

  /* Config */
  extmem_list_config[1].PsramObject.psram_public.config[0].WriteMask = 0x40u;
  extmem_list_config[1].PsramObject.psram_public.config[0].WriteValue = 0x40u;
  extmem_list_config[1].PsramObject.psram_public.config[0].REGAddress = 0x08u;

  /* Memory command configuration */
  extmem_list_config[1].PsramObject.psram_public.ReadREG           = 0x40u;
  extmem_list_config[1].PsramObject.psram_public.WriteREG          = 0xC0u;
  extmem_list_config[1].PsramObject.psram_public.ReadREGSize       = 2u;
  extmem_list_config[1].PsramObject.psram_public.REG_DummyCycle    = 4u;
  extmem_list_config[1].PsramObject.psram_public.Write_command     = 0xA0u;
  extmem_list_config[1].PsramObject.psram_public.Write_DummyCycle  = 4u;
  extmem_list_config[1].PsramObject.psram_public.Read_command      = 0x20u;
  extmem_list_config[1].PsramObject.psram_public.WrapRead_command  = 0x00u;
  extmem_list_config[1].PsramObject.psram_public.Read_DummyCycle   = 4u;

  // EXTMEM_Init(EXTMEMORY_1, HAL_RCCEx_GetPeriphCLKFreq(RCC_PERIPHCLK_XSPI2));
  // EXTMEM_Init(EXTMEMORY_2, HAL_RCCEx_GetPeriphCLKFreq(RCC_PERIPHCLK_XSPI1));

  /* USER CODE BEGIN MX_EXTMEM_Init_PostTreatment */
  EXTMEM_Flash_Probe();
  EXTMEM_Flash_EnterXIP();
  EXTMEM_PSRAM_Probe();
  EXTMEM_PSRAM_EnterXIP();

  // EXTMEM_MemoryMappedMode(EXTMEMORY_2, EXTMEM_ENABLE);

  /* USER CODE END MX_EXTMEM_Init_PostTreatment */
}
