/*
 * ft5xx6.cpp
 *
 *  Created on: Aug 15, 2021
 *      Author: huang
 */

#include "Ft5xx6.hpp"
#include "cmsis_os.h"
#include <cstdio>

#define FT5xx6_I2C_ID       0x70

const uint16_t FT5xx6_TPX_TBL[5]={FT_TP1_REG,FT_TP2_REG,FT_TP3_REG,FT_TP4_REG,FT_TP5_REG};

Ft5xx6::Ft5xx6() {
    // TODO Auto-generated constructor stub
}

Ft5xx6::Ft5xx6(I2C_HandleTypeDef *_touchPad_IIC_Handle) :
touchPad_IIC_Handle { _touchPad_IIC_Handle }{
    // TODO Auto-generated constructor stub
    ft5xx6_iic.init(touchPad_IIC_Handle, FT5xx6_I2C_ID);
}

bool Ft5xx6::init(void)
{
    uint8_t buffer[2]; 
    // HAL_GPIO_WritePin(TP_RST_GPIO_Port, TP_RST_Pin, GPIO_PIN_RESET);
    // HAL_Delay(20);
    // HAL_GPIO_WritePin(TP_RST_GPIO_Port, TP_RST_Pin, GPIO_PIN_SET);
    // HAL_Delay(100);
    ft5xx6_iic.writeByte(FT_DEVIDE_MODE, 0x00);     //进入正常操作模式
    ft5xx6_iic.writeByte(FT_ID_G_MODE, 0x00);       //查询模式
    ft5xx6_iic.writeByte(FT_ID_G_THGROUP, 22);      //设置触摸有效值，越小越灵敏
    ft5xx6_iic.writeByte(FT_ID_G_PERIODACTIVE, 12); //激活周期，不能小于12，最大14
    //读取版本号，参考值：0x3003
    ft5xx6_iic.readBytes(FT_ID_G_LIB_VERSION, &buffer[0], 2);
	//print("Ft5xx6 ID:0x%02X%02X\r\n", buffer[0], buffer[1]);//问题记录：打开次行代码后，触摸触摸屏时就会死机
    if((buffer[0]==0X30&&buffer[1]==0X03)||buffer[1]==0X01||buffer[1]==0X02) { //版本:0X3003/0X0001/0X0002
        return false;
    }
    return true;
}

//扫描触摸屏(采用查询方式)
//mode:0,正常扫描.
//返回值:当前触屏状态.
//0,触屏无触摸;1,触屏有触摸
uint8_t Ft5xx6::readData(uint16_t &x, uint16_t &y)
{
    uint8_t buffer[4];
    uint8_t points = 0;
    points = ft5xx6_iic.readByte(FT_REG_NUM_FINGER);//读取触摸点的数量
    if (points > 0 && points < 6) {
        for( uint8_t i = 0; i < 1; i++ ){
            ft5xx6_iic.readBytes(FT5xx6_TPX_TBL[i], buffer, 4);//读取XY坐标值
            y = ( (uint16_t)( buffer[0] & 0X0F ) << 8) + buffer[1];
            x = ( (uint16_t)( buffer[2] & 0X0F ) << 8) + buffer[3];
        }
        // printf("points:%d x = %d, y = %d\r\n", points, x, y);
    }
    return points;
}

Ft5xx6::~Ft5xx6() {
    // TODO Auto-generated destructor stub
}

