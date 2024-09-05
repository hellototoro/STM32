/*
 * led.cpp
 *
 *  Created on: Aug 1, 2021
 *      Author: huang
 */

#include "led/Led.hpp"

namespace MyDrivers {

Led::Led(int _number) : number { _number }
{
}

void Led::switch_led(bool_switch _switch)
{
    switch(number)
    {
        case static_cast<int>(led_number::number1):
            HAL_GPIO_WritePin(LED_BLUE_GPIO_Port, LED_BLUE_Pin, static_cast<GPIO_PinState>(_switch));
            break;
        case static_cast<int>(led_number::number2):
            HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, static_cast<GPIO_PinState>(_switch));
            break;
        default:
            break;
    }
}

void Led::on(void)
{
    switch_led(OFF);
}

void Led::off(void)
{
    switch_led(ON);
}

void Led::toggle(void)
{
    switch(number)
    {
        case static_cast<int>(led_number::number1):
        HAL_GPIO_TogglePin(LED_BLUE_GPIO_Port, LED_BLUE_Pin);
            break;
        case static_cast<int>(led_number::number2):
        HAL_GPIO_TogglePin(LED_RED_GPIO_Port, LED_RED_Pin);
            break;
        default:
            break;
    }
}

}
