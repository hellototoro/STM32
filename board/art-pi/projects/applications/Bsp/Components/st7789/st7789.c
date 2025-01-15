/*
 * st7789.c
 *
 *  Created on: 2025年1月13日
 *      Author: huang
 */
/****************************************************************************************************
//=========================================电源接线================================================//
//     LCD模块                STM32单片机
//      VCC          接        DC5V/3.3V      //电源
//      GND          接          GND          //电源地
//=======================================液晶屏数据线接线==========================================//
//本模块默认数据总线类型为SPI总线
//     LCD模块                STM32单片机    
//    SDI(MOSI)      接          PB0         //液晶屏SPI总线数据写信号
//    SDO(MISO)      接          Pxx         //液晶屏SPI总线数据读信号，如果不需要读，可以不接线
//=======================================液晶屏控制线接线==========================================//
//     LCD模块                 STM32单片机 
//       LED         接          Pxx         //液晶屏背光控制信号，如果不需要控制，接5V或3.3V
//       SCK         接          PH3         //液晶屏SPI总线时钟信号
//     LCD_RS        接          PB2         //液晶屏数据/命令控制信号
//     LCD_RST       接          PH2         //液晶屏复位控制信号
//     LCD_CS        接          PB1         //液晶屏片选控制信号
//=========================================触摸屏触接线=========================================//
//如果模块不带触摸功能或者带有触摸功能，但是不需要触摸功能，则不需要进行触摸屏接线
//	   LCD模块                STM32单片机 
//     CTP_INT       接          Pxx         //电容触摸屏中断信号
//     CTP_SDA       接          Pxx         //电容触摸屏IIC数据信号
//     CTP_RST       接          Pxx         //电容触摸屏复位信号
//     CTP_SCL       接          Pxx         //电容触摸屏IIC时钟信号
**************************************************************************************************/	

#include "st7789.h"

static void SPI_WriteByte(uint8_t byte)
{
    uint8_t n;
    for(n = 0; n < 8; n++)
    {
        if(byte & 0x80) HAL_GPIO_WritePin(SPI_PANEL_MOSI_GPIO_Port, SPI_PANEL_MOSI_Pin, GPIO_PIN_SET);
        else            HAL_GPIO_WritePin(SPI_PANEL_MOSI_GPIO_Port, SPI_PANEL_MOSI_Pin, GPIO_PIN_RESET);
        byte <<= 1;
        HAL_GPIO_WritePin(SPI_PANEL_SCK_GPIO_Port, SPI_PANEL_SCK_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(SPI_PANEL_SCK_GPIO_Port, SPI_PANEL_SCK_Pin, GPIO_PIN_SET);
    }
}

static void SPI_WriteComm(uint8_t cmd)
{
    HAL_GPIO_WritePin(SPI_PANEL_CS_GPIO_Port, SPI_PANEL_CS_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(SPI_PANEL_RS_GPIO_Port, SPI_PANEL_RS_Pin, GPIO_PIN_RESET);
    SPI_WriteByte(cmd);
    HAL_GPIO_WritePin(SPI_PANEL_CS_GPIO_Port, SPI_PANEL_CS_Pin, GPIO_PIN_SET);
}

static void SPI_WriteData(uint8_t data)
{
    HAL_GPIO_WritePin(SPI_PANEL_CS_GPIO_Port, SPI_PANEL_CS_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(SPI_PANEL_RS_GPIO_Port, SPI_PANEL_RS_Pin, GPIO_PIN_SET);
    SPI_WriteByte(data);
    HAL_GPIO_WritePin(SPI_PANEL_CS_GPIO_Port, SPI_PANEL_CS_Pin, GPIO_PIN_SET);
}

void LCD_Clear(uint16_t Color)
{
    uint16_t i,m;
    HAL_GPIO_WritePin(SPI_PANEL_CS_GPIO_Port, SPI_PANEL_CS_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(SPI_PANEL_RS_GPIO_Port, SPI_PANEL_RS_Pin, GPIO_PIN_SET);
    for(i=0;i<320;i++)
    {
        for(m=0;m<240;m++)
        {
            SPI_WriteByte(Color>>8);
            SPI_WriteByte(Color);
        }
    }
    HAL_GPIO_WritePin(SPI_PANEL_CS_GPIO_Port, SPI_PANEL_CS_Pin, GPIO_PIN_SET);
}

void st7789_init(void)
{  
    HAL_GPIO_WritePin(SPI_PANEL_RST_GPIO_Port, SPI_PANEL_RST_Pin, GPIO_PIN_SET);
    HAL_Delay(50);
    HAL_GPIO_WritePin(SPI_PANEL_RST_GPIO_Port, SPI_PANEL_RST_Pin, GPIO_PIN_RESET);
    HAL_Delay(100);
    HAL_GPIO_WritePin(SPI_PANEL_RST_GPIO_Port, SPI_PANEL_RST_Pin, GPIO_PIN_SET);
    HAL_Delay(50);

    // HAL_GPIO_WritePin(SPI_PANEL_CS_GPIO_Port, SPI_PANEL_CS_Pin, GPIO_PIN_SET);
    // HAL_Delay(20);
    // HAL_GPIO_WritePin(SPI_PANEL_CS_GPIO_Port, SPI_PANEL_CS_Pin, GPIO_PIN_RESET);

//************* ST7789初始化**********//	
    SPI_WriteComm(0x36);
    SPI_WriteData(0x00);

    SPI_WriteComm(0x2A);
    SPI_WriteData(0x00);
    SPI_WriteData(0x00);
    SPI_WriteData(0x00);
    SPI_WriteData(0xEF);

    SPI_WriteComm(0x2B);
    SPI_WriteData(0x00);
    SPI_WriteData(0x00);
    SPI_WriteData(0x01);
    SPI_WriteData(0x3f);

    SPI_WriteComm(0x3A);
    SPI_WriteData(0x05);

    SPI_WriteComm(0xB2);
    SPI_WriteData(0x0C);
    SPI_WriteData(0x0C);
    SPI_WriteData(0x00);
    SPI_WriteData(0x33);
    SPI_WriteData(0x33);

    SPI_WriteComm(0xB7);
    SPI_WriteData(0x35);

    SPI_WriteComm(0xBB);
    SPI_WriteData(0x19);

    SPI_WriteComm(0xC0);
    SPI_WriteData(0x2C);

    SPI_WriteComm(0xC2);
    SPI_WriteData(0x01);

    SPI_WriteComm(0xC3);
    SPI_WriteData(0x12);

    SPI_WriteComm(0xC4);
    SPI_WriteData(0x20);

    SPI_WriteComm(0xC6);
    SPI_WriteData(0x0F);

    SPI_WriteComm(0xD0);
    SPI_WriteData(0xA4);
    SPI_WriteData(0xA1);

    SPI_WriteComm(0xE0);
    SPI_WriteData(0xD0);
    SPI_WriteData(0x04);
    SPI_WriteData(0x0D);
    SPI_WriteData(0x11);
    SPI_WriteData(0x13);
    SPI_WriteData(0x2B);
    SPI_WriteData(0x3F);
    SPI_WriteData(0x54);
    SPI_WriteData(0x4C);
    SPI_WriteData(0x18);
    SPI_WriteData(0x0D);
    SPI_WriteData(0x0B);
    SPI_WriteData(0x1F);
    SPI_WriteData(0x23);

    SPI_WriteComm(0xE1);
    SPI_WriteData(0xD0);
    SPI_WriteData(0x04);
    SPI_WriteData(0x0C);
    SPI_WriteData(0x11);
    SPI_WriteData(0x13);
    SPI_WriteData(0x2C);
    SPI_WriteData(0x3F);
    SPI_WriteData(0x44);
    SPI_WriteData(0x51);
    SPI_WriteData(0x2F);
    SPI_WriteData(0x1F);
    SPI_WriteData(0x1F);
    SPI_WriteData(0x20);
    SPI_WriteData(0x23);

    SPI_WriteComm(0x11);
    // Delay(120);

    SPI_WriteComm(0x29);
    SPI_WriteComm(0x2C);

    LCD_Clear(0x001F);//清全屏白色
}
