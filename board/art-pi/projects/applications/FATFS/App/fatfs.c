/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file   fatfs.c
  * @brief  Code for fatfs applications
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
#include "fatfs.h"
#include <stdio.h>

uint8_t retSD;    /* Return value for SD */
char SDPath[4];   /* SD logical drive path */
FATFS SDFatFS;    /* File system object for SD logical drive */
FIL SDFile;       /* File object for SD */

/* USER CODE BEGIN Variables */
typedef enum {
    CARD_CONNECTED,
    CARD_DISCONNECTED,
    CARD_STATUS_CHANGED,
} SD_ConnectionStateTypeDef;

osMessageQId ConnectionEvent;

extern void sdcard_test(void);

void DetectSDCardEntry(void const * argument);
void FS_FileOperations(void);

/* USER CODE END Variables */

void MX_FATFS_Init(void)
{
  /*## FatFS: Link the SD driver ###########################*/
  retSD = FATFS_LinkDriver(&SD_Driver, SDPath);

  /* USER CODE BEGIN Init */
  /* additional user code for init */
  /* USER CODE END Init */
}

/**
  * @brief  Gets Time from RTC
  * @param  None
  * @retval Time in DWORD
  */
DWORD get_fattime(void)
{
  /* USER CODE BEGIN get_fattime */
  return 0;
  /* USER CODE END get_fattime */
}

/* USER CODE BEGIN Application */
uint8_t BSP_SD_IsDetected(void)
{
    return BSP_PlatformIsDetected() ? SD_NOT_PRESENT : SD_PRESENT;
}

void FS_AppThread(void const * argument)
{
    (void) argument;
    osEvent event;

    osThreadDef(DetectSDCard, DetectSDCardEntry, osPriorityNormal, 0, 2 * configMINIMAL_STACK_SIZE);
    osThreadId DetectSDCardHandle = osThreadCreate(osThread(DetectSDCard), NULL);
    (void) DetectSDCardHandle;

    for(;;) {
        event = osMessageGet( ConnectionEvent, osWaitForever );
        if (event.status == osEventMessage) {
            switch (event.value.v) {
                case CARD_CONNECTED:
                    BSP_SD_Init();
                    sdcard_test();
                    FS_FileOperations();
                    break;

                case CARD_DISCONNECTED:
                    break;

                default:
                    break;
            }
        }
    }
}

void DetectSDCardEntry(void const * argument)
{
    (void) argument;
    SD_ConnectionStateTypeDef state = CARD_DISCONNECTED;

    for(;;) {
        if ((BSP_SD_IsDetected() == SD_PRESENT) && (state == CARD_DISCONNECTED)) {
            state = CARD_CONNECTED;
            osMessagePut(ConnectionEvent, CARD_CONNECTED, osWaitForever);
        } else if ((BSP_SD_IsDetected() == SD_NOT_PRESENT) && (state == CARD_CONNECTED)) {
            state = CARD_DISCONNECTED;
            osMessagePut(ConnectionEvent, CARD_DISCONNECTED, osWaitForever);
        }
        osDelay(500);
    }
}

static uint8_t isFsCreated = 0;
uint8_t workBuffer[2 * _MAX_SS];
/* 
 * ensure that the read buffer 'rtext' is 32-Byte aligned in address and size
 * to guarantee that any other data in the cache won't be affected when the 'rtext'
 * is being invalidated.
 */
ALIGN_32BYTES(uint8_t rtext[64]);
void FS_FileOperations(void)
{
    FRESULT res;                                          /* FatFs function common result code */
    uint32_t byteswritten, bytesread;                     /* File write/read counts */
    uint8_t wtext[] = "This is STM32 working with FatFs uSD + FreeRTOS"; /* File write buffer */

    /* Register the file system object to the FatFs module */
    if(f_mount(&SDFatFS, (TCHAR const*)SDPath, 0) == FR_OK)
    {
        printf("FatFs mounted successfully!\r\n");
        /* check whether the FS has been already created */
        if (isFsCreated == 0)
        {
            if(f_mkfs(SDPath, FM_FAT32, 0, workBuffer, sizeof(workBuffer)) != FR_OK)
            {
                printf("Failed to create file system!\r\n");
                return;
            }
            isFsCreated = 1;
        }
        /* Create and Open a new text file object with write access */
        if(f_open(&SDFile, "STM32.TXT", FA_CREATE_ALWAYS | FA_WRITE) == FR_OK) 
        {
            printf("File created successfully!\r\n");
            /* Write data to the text file */
            res = f_write(&SDFile, wtext, sizeof(wtext), (void *)&byteswritten);

            if((byteswritten > 0) && (res == FR_OK))
            {
                /* Close the open text file */
                f_close(&SDFile);

                /* Open the text file object with read access */
                if(f_open(&SDFile, "STM32.TXT", FA_READ) == FR_OK)
                {
                    /* Read data from the text file */
                    res = f_read(&SDFile, rtext, sizeof(rtext), (void *)&bytesread);

                    if((bytesread > 0) && (res == FR_OK))
                    {
                        /* Close the open text file */
                        f_close(&SDFile);

                        /* Compare read data with the expected data */
                        if((bytesread == byteswritten))
                        {                             
                            /* Success of the demo: no error occurrence */
                            // BSP_LED_On(LED1);
                            printf("File read successfully!\r\n");
                            return;
                        }
                    }
                }
            }
        }
    }
    printf("FatFs operation failed!\r\n");
}

/* USER CODE END Application */
