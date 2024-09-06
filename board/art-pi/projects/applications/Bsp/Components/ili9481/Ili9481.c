/*
 * Ili9481.c
 *
 *  Created on: 2024年8月21日
 *      Author: huang
 */

#include "Ili9481.h"

static void SPI_WriteByte(uint8_t byte)
{
    uint8_t n;
    for(n = 0; n < 8; n++)
    {
        if(byte & 0x80) HAL_GPIO_WritePin(LCD_MOSI_GPIO_Port, LCD_MOSI_Pin, GPIO_PIN_SET);
        else HAL_GPIO_WritePin(LCD_MOSI_GPIO_Port, LCD_MOSI_Pin, GPIO_PIN_RESET);
        byte <<= 1;
        HAL_GPIO_WritePin(LCD_SCK_GPIO_Port, LCD_SCK_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(LCD_SCK_GPIO_Port, LCD_SCK_Pin, GPIO_PIN_SET);
    }
}

static void SPI_WriteComm(uint8_t cmd)
{
    HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LCD_MOSI_GPIO_Port, LCD_MOSI_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LCD_SCK_GPIO_Port, LCD_SCK_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LCD_SCK_GPIO_Port, LCD_SCK_Pin, GPIO_PIN_SET);
    SPI_WriteByte(cmd);
    HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_SET);
}

static void SPI_WriteData(uint8_t data)
{
    HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LCD_MOSI_GPIO_Port, LCD_MOSI_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(LCD_SCK_GPIO_Port, LCD_SCK_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LCD_SCK_GPIO_Port, LCD_SCK_Pin, GPIO_PIN_SET);
    SPI_WriteByte(data);
    HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_SET);
}

void Ili9481_init(void)
{
    HAL_GPIO_WritePin(TP_RST_GPIO_Port, TP_RST_Pin, GPIO_PIN_RESET);
    HAL_Delay(20);
    HAL_GPIO_WritePin(TP_RST_GPIO_Port, TP_RST_Pin, GPIO_PIN_SET);

    HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_SET);
    HAL_Delay(20);
    HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_RESET);

    SPI_WriteComm(0x11);
    HAL_Delay(20);

    SPI_WriteComm(0xD0);
    SPI_WriteData(0x07);
    SPI_WriteData(0x42);
    SPI_WriteData(0x19);

    SPI_WriteComm(0xD1);
    SPI_WriteData(0x00);
    SPI_WriteData(0x14);
    SPI_WriteData(0x1B);

    SPI_WriteComm(0xD2);
    SPI_WriteData(0x01);
    SPI_WriteData(0x12);

    SPI_WriteComm(0xC0);
    SPI_WriteData(0x00);
    SPI_WriteData(0x3B);
    SPI_WriteData(0x00);
    SPI_WriteData(0x02);
    SPI_WriteData(0x01);

    SPI_WriteComm(0xC5);
    SPI_WriteData(0x00);

    SPI_WriteComm(0xC8);
    SPI_WriteData(0x00);
    SPI_WriteData(0x46);
    SPI_WriteData(0x44);
    SPI_WriteData(0x50);
    SPI_WriteData(0x04);
    SPI_WriteData(0x16);
    SPI_WriteData(0x33);
    SPI_WriteData(0x13);
    SPI_WriteData(0x77);
    SPI_WriteData(0x05);
    SPI_WriteData(0x0F);
    SPI_WriteData(0x00);

    SPI_WriteComm(0xB4);
    SPI_WriteData(0x10);

    SPI_WriteComm(0x36);
    SPI_WriteData(0x80); //0x88
    SPI_WriteComm(0x3A);
    SPI_WriteData(0x66); //0x55

    SPI_WriteComm(0x2A);
    SPI_WriteData(0x00);
    SPI_WriteData(0x00);
    SPI_WriteData(0x01);
    SPI_WriteData(0x3F);

    SPI_WriteComm(0x2B);
    SPI_WriteData(0x00);
    SPI_WriteData(0x00);
    SPI_WriteData(0x01);
    SPI_WriteData(0xdf);
    HAL_Delay(120);
    SPI_WriteComm(0x29);
    SPI_WriteComm(0x2C);

    HAL_Delay(10);
}

