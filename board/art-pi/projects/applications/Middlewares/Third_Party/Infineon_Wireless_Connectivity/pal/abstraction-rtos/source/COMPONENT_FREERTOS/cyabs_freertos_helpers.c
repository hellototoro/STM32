/***********************************************************************************************//**
 * \file cyabs_freertos_helpers.c
 *
 * \brief
 * Provides implementations for functions required to enable static allocation and
 * tickless mode in FreeRTOS.
 *
 ***************************************************************************************************
 * \copyright
 * Copyright 2018-2022 Cypress Semiconductor Corporation (an Infineon company) or
 * an affiliate of Cypress Semiconductor Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 **************************************************************************************************/
#include "FreeRTOS.h"
#include "task.h"
#include "cyabs_rtos.h"
#if defined(CY_USING_HAL)
#include "cyhal.h"
#endif

// This is included to allow the user to control the idle task behavior via the configurator
// System->Power->RTOS->System Idle Power Mode setting.
#include "cybsp.h"

#define pdTICKS_TO_MS(xTicks)    ( ( ( TickType_t ) ( xTicks ) * 1000u ) / configTICK_RATE_HZ )

#if defined(CY_USING_HAL)
static cyhal_lptimer_t* _timer = NULL;

//--------------------------------------------------------------------------------------------------
// cyabs_rtos_set_lptimer
//--------------------------------------------------------------------------------------------------
void cyabs_rtos_set_lptimer(cyhal_lptimer_t* timer)
{
    _timer = timer;
}


//--------------------------------------------------------------------------------------------------
// cyabs_rtos_get_lptimer
//--------------------------------------------------------------------------------------------------
cyhal_lptimer_t* cyabs_rtos_get_lptimer(void)
{
    return _timer;
}


#endif //defined(CY_USING_HAL)


#if defined(CY_USING_HAL) && (configUSE_TICKLESS_IDLE != 0)
//--------------------------------------------------------------------------------------------------
// vApplicationSleep
//
/** User defined tickless idle sleep function.
 *
 * Provides a implementation for portSUPPRESS_TICKS_AND_SLEEP macro that allows
 * the device to attempt to deep-sleep for the idle time the kernel expects before
 * the next task is ready. This function disables the system timer and enables low power
 * timer that can operate in deep-sleep mode to wake the device from deep-sleep after
 * expected idle time has elapsed.
 *
 * @param[in] xExpectedIdleTime     Total number of tick periods before
 *                                  a task is due to be moved into the Ready state.
 */
//--------------------------------------------------------------------------------------------------
__WEAK void vApplicationSleep(TickType_t xExpectedIdleTime)
{
    static cyhal_lptimer_t timer;
    uint32_t               actual_sleep_ms = 0;

    if (NULL == _timer)
    {
        cy_rslt_t result = cyhal_lptimer_init(&timer);
        if (result == CY_RSLT_SUCCESS)
        {
            _timer = &timer;
        }
        else
        {
            CY_ASSERT(false);
        }
    }

    if (NULL != _timer)
    {
        /* Disable interrupts so that nothing can change the status of the RTOS while
         * we try to go to sleep or deep-sleep.
         */
        uint32_t         status       = cyhal_system_critical_section_enter();
        eSleepModeStatus sleep_status = eTaskConfirmSleepModeStatus();

        if (sleep_status != eAbortSleep)
        {
            // By default, the device will deep-sleep in the idle task unless if the device
            // configurator overrides the behaviour to sleep in the System->Power->RTOS->System
            // Idle Power Mode setting.
            bool deep_sleep = true;
            #if defined (CY_CFG_PWR_SYS_IDLE_MODE)
            // If the system needs to operate in active mode the tickless mode should not be used in
            // FreeRTOS
            CY_ASSERT(CY_CFG_PWR_SYS_IDLE_MODE != CY_CFG_PWR_MODE_ACTIVE);
            deep_sleep =
                #if defined(CY_CFG_PWR_MODE_DEEPSLEEP_RAM)
                ((CY_CFG_PWR_SYS_IDLE_MODE & CY_CFG_PWR_MODE_DEEPSLEEP_RAM) ==
                 CY_CFG_PWR_MODE_DEEPSLEEP_RAM) ||
                #endif
                ((CY_CFG_PWR_SYS_IDLE_MODE & CY_CFG_PWR_MODE_DEEPSLEEP) ==
                 CY_CFG_PWR_MODE_DEEPSLEEP);
            #endif // if defined (CY_CFG_PWR_SYS_IDLE_MODE)
            uint32_t sleep_ms = pdTICKS_TO_MS(xExpectedIdleTime);
            cy_rslt_t result;
            if (deep_sleep)
            {
                // Adjust the deep-sleep time by the sleep/wake latency if set.
                #if defined(CY_CFG_PWR_DEEPSLEEP_LATENCY)
                if (sleep_ms > CY_CFG_PWR_DEEPSLEEP_LATENCY)
                {
                    sleep_ms -= CY_CFG_PWR_DEEPSLEEP_LATENCY;
                    result = cyhal_syspm_tickless_deepsleep(_timer, sleep_ms, &actual_sleep_ms);
                }
                else
                {
                    result = CY_RTOS_TIMEOUT;
                }
                #else // defined(CY_CFG_PWR_DEEPSLEEP_LATENCY)
                result = cyhal_syspm_tickless_deepsleep(_timer, sleep_ms, &actual_sleep_ms);
                #endif // defined(CY_CFG_PWR_DEEPSLEEP_LATENCY)
                //maintain compatibility with older HAL versions that didn't define this error
                #ifdef CYHAL_SYSPM_RSLT_DEEPSLEEP_LOCKED
                //Deepsleep has been locked, continuing into normal sleep
                if (result == CYHAL_SYSPM_RSLT_DEEPSLEEP_LOCKED)
                {
                    deep_sleep = false;
                }
                #endif
            }
            if (!deep_sleep)
            {
                result = cyhal_syspm_tickless_sleep(_timer, sleep_ms, &actual_sleep_ms);
            }

            if (result == CY_RSLT_SUCCESS)
            {
                // If you hit this assert, the latency time (CY_CFG_PWR_DEEPSLEEP_LATENCY) should
                // be increased. This can be set though the Device Configurator, or by manually
                // defining the variable.
                CY_ASSERT(actual_sleep_ms <= pdTICKS_TO_MS(xExpectedIdleTime));
                vTaskStepTick(convert_ms_to_ticks(actual_sleep_ms));
            }
        }

        cyhal_system_critical_section_exit(status);
    }
}


#endif // defined(CY_USING_HAL) && (configUSE_TICKLESS_IDLE != 0)
