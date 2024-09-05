/*
 * hwiic.cpp
 *
 *  Created on: Aug 15, 2021
 *      Author: huang
 */

#include "hw_iic.hpp"

namespace MyDrivers {

#define I2C_TIMEOUT  1000 /*<! Value of Timeout when I2C communication fails */

HW_I2C::HW_I2C() {
    // TODO Auto-generated constructor stub

}

void HW_I2C::init(I2C_HandleTypeDef *IIC_Handle,uint8_t deviceAddress)
{
    this->IIC_Handle = IIC_Handle;
    this->deviceAddress = deviceAddress;
}

void HW_I2C::error(void)
{
    /* De-initialize the IOE comunication BUS */
    //HAL_I2C_DeInit(I2C_Handle);

    /* Re-Initiaize the IOE comunication BUS */
    //I2Cx_Init();
    HAL_I2C_MspInit(IIC_Handle);
    HAL_I2C_Init(IIC_Handle);
}

uint8_t HW_I2C::readByte(uint8_t regAddress)
{
    HAL_StatusTypeDef status = HAL_OK;
    uint8_t Value = 0;

    status = HAL_I2C_Mem_Read(IIC_Handle, deviceAddress, regAddress, I2C_MEMADD_SIZE_8BIT, &Value, 1, I2C_TIMEOUT);

    /* Check the communication status */
    if(status != HAL_OK)
    {
        /* Execute user timeout callback */
        error();
    }

    return Value;
}

bool HW_I2C::readBytes(uint8_t regAddress, uint8_t *pData, uint16_t size)
{
    HAL_StatusTypeDef status = HAL_OK;

    status = HAL_I2C_Mem_Read(IIC_Handle, deviceAddress, regAddress, I2C_MEMADD_SIZE_8BIT, pData, size, I2C_TIMEOUT);

    /* Check the communication status */
    if(status != HAL_OK)
    {
        /* Execute user timeout callback */
        error();
    }

    return static_cast<bool>(status);
}

bool HW_I2C::writeByte(uint8_t regAddress, uint8_t data)
{
    HAL_StatusTypeDef status = HAL_OK;

    status = HAL_I2C_Mem_Write(IIC_Handle, deviceAddress, (uint16_t)regAddress, I2C_MEMADD_SIZE_8BIT, &data, 1, I2C_TIMEOUT);

    /* Check the communication status */
    if(status != HAL_OK)
    {
        /* I2C error occured */
        error();
    }

    return static_cast<bool>(status);
}

bool HW_I2C::writeBytes(uint8_t regAddress, uint8_t *pdata, uint16_t size)
{
    HAL_StatusTypeDef status = HAL_OK;

    status = HAL_I2C_Mem_Write(IIC_Handle, deviceAddress, (uint16_t)regAddress, I2C_MEMADD_SIZE_8BIT, pdata, size, I2C_TIMEOUT);

    /* Check the communication status */
    if(status != HAL_OK)
    {
        /* Re-Initiaize the I2C Bus */
        error();
    }

    return static_cast<bool>(status);
}


HW_I2C::~HW_I2C() {
    // TODO Auto-generated destructor stub
}

} /* namespace MyDrivers */
