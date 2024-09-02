/*
 * sdcard_test.c
 *
 *  Created on: 2024年8月21日
 *      Author: huang
 */

#include <stdio.h>
#include "sdcard_test.h"
#include "stm32h7xx_hal.h"

extern SD_HandleTypeDef hsd1;

void sdcard_test(void)
{
    int sdcard_status = 0;
    HAL_SD_CardCIDTypeDef sdcard_cid;

    printf("Micro SD Card Test...\r\n");

    /* 检测SD卡是否正常（处于数据传输模式的传输状态） */
    sdcard_status = HAL_SD_GetCardState(&hsd1);
    if(sdcard_status == HAL_SD_CARD_TRANSFER)
    {
        printf("SD card init ok!\r\n\r\n");

        //打印SD卡基本信息
        printf("SD card information!\r\n");
        printf("Card Block Number: %ld\r\n", hsd1.SdCard.BlockNbr);
        printf("Card Version:      %ld \r\n",hsd1.SdCard.CardVersion);
        printf("Card Class:        %ld \r\n",hsd1.SdCard.Class);
        printf("Card Type:         %ld \r\n",hsd1.SdCard.CardType);
        printf("Card Speed:        %ld \r\n",hsd1.SdCard.CardSpeed);

        //读取并打印SD卡的CID信息
        HAL_SD_GetCardCID(&hsd1,&sdcard_cid);
        printf("ManufacturerID:    %d \r\n",sdcard_cid.ManufacturerID);
    }
    else
    { 
        printf("SD card init fail!\r\n" );
    }
}
