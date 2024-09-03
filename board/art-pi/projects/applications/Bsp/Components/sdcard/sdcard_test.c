/*
 * sdcard_test.c
 *
 *  Created on: 2024年8月21日
 *      Author: huang
 */

#include <stdio.h>
#include "sdcard_test.h"
#include "stm32h7xx_hal.h"
#include "cmsis_os.h"

extern SD_HandleTypeDef hsd1;

void sdcard_test(void)
{
    int sdcard_status = 0;
    HAL_SD_CardCIDTypeDef sdcard_cid;

    printf("Micro SD Card Test...\r\n");

    /* 检测SD卡是否正常（处于数据传输模式的传输状态） */
    sdcard_status = HAL_SD_GetCardState(&hsd1);
    if(sdcard_status == HAL_SD_CARD_TRANSFER) {
        printf("SD card init ok!\r\n\r\n");

        //打印SD卡基本信息
        printf("SD card information!\r\n");
        printf("Card Block Number: %ld \r\n", hsd1.SdCard.BlockNbr);
        printf("Card Version:      %ld \r\n", hsd1.SdCard.CardVersion);
        printf("Card Class:        %ld \r\n", hsd1.SdCard.Class);
        printf("Card Type:         %ld \r\n", hsd1.SdCard.CardType);
        printf("Card Speed:        %ld \r\n", hsd1.SdCard.CardSpeed);
        if(hsd1.SdCard.CardSpeed == CARD_NORMAL_SPEED) {
            printf("Normal Speed Card <12.5MB/S, MAX Clock < 25MHz, Spec Version 1.01\r\n");
        } else if (hsd1.SdCard.CardSpeed == CARD_HIGH_SPEED) {
            printf("High Speed Card <25MB/s, MAX Clock < 50MHz, Spec Version 2.00\r\n");
        } else if (hsd1.SdCard.CardSpeed == CARD_ULTRA_HIGH_SPEED) {
            printf("UHS-I SD Card <50MB/S for SDR50, DDR50 Cards, MAX Clock < 50MHz OR 100MHz\r\n");
            // printf("UHS-I SD Card <104MB/S for SDR104, MAX Clock < 108MHz, Spec version 3.01\r\n");
        }

        HAL_SD_GetCardCID(&hsd1,&sdcard_cid);
        printf("ManufacturerID:    %d \r\n",sdcard_cid.ManufacturerID);
    } else {
        printf("SD card init fail!\r\n" );
    }
}
