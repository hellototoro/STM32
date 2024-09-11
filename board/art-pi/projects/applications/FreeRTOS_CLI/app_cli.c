/*
 * app_cli.c
 *
 *  Created on: 2024年9月11日
 *      Author: huang jian
 */
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

#include "cmsis_os.h"
#include "app_cli.h"
#include "cli_commands.h"
#include "main.h"

#define MAX_INPUT_LENGTH 50
#define USING_VS_CODE_TERMINAL 1
#define USING_OTHER_TERMINAL 0 // e.g. Putty, TerraTerm

char cOutputBuffer[configCOMMAND_INT_MAX_OUTPUT_SIZE], pcInputString[MAX_INPUT_LENGTH];
int8_t cRxedChar;
const char * cli_prompt = "\r\ncli>";
/* CLI escape sequences*/
uint8_t backspace[] = "\b \b";
uint8_t backspace_tt[] = " \b";

osThreadId cliTaskHandle;

extern UART_HandleTypeDef huart4;

/*************************************************************************************************/
void cliWrite(const char *str)
{
   printf("%s", str);
   // flush stdout
   fflush(stdout);
}

/*************************************************************************************************/
void handleNewline(const char *const pcInputString, char *cOutputBuffer, uint8_t *cInputIndex)
{
    cliWrite("\r\n");

    BaseType_t xMoreDataToFollow;
    do
    {     
        xMoreDataToFollow = FreeRTOS_CLIProcessCommand(pcInputString, cOutputBuffer, configCOMMAND_INT_MAX_OUTPUT_SIZE);
        cliWrite(cOutputBuffer);
    } while (xMoreDataToFollow != pdFALSE);

    cliWrite(cli_prompt);
    *cInputIndex = 0;
    memset((void*)pcInputString, 0x00, MAX_INPUT_LENGTH);
}

/*************************************************************************************************/
void handleBackspace(uint8_t *cInputIndex, char *pcInputString)
{
    if (*cInputIndex > 0)
    {
        (*cInputIndex)--;
        pcInputString[*cInputIndex] = '\0';

#if USING_VS_CODE_TERMINAL
        cliWrite((char *)backspace);
#elif USING_OTHER_TERMINAL
        cliWrite((char *)backspace_tt);
#endif
    }
    else
    {
#if USING_OTHER_TERMINAL
        uint8_t right[] = "\x1b\x5b\x43";
        cliWrite((char *)right);
#endif
    }
}

/*************************************************************************************************/
void handleCharacterInput(uint8_t *cInputIndex, char *pcInputString)
{
    if (cRxedChar == '\r')
    {
        return;
    }
    else if (cRxedChar == (uint8_t)0x08 || cRxedChar == (uint8_t)0x7F)
    {
        handleBackspace(cInputIndex, pcInputString);
    }
    else
    {
        if (*cInputIndex < MAX_INPUT_LENGTH)
        {
            pcInputString[*cInputIndex] = cRxedChar;
            (*cInputIndex)++;
        }
    }
}

/*************************************************************************************************/
void StartCliTask(void *pvParameters)
{
    UNUSED(pvParameters);
    uint8_t cInputIndex = 0;    // simply used to keep track of the index of the input string
    uint32_t receivedValue;     // used to store the received value from the notification

    vRegisterCLICommands();
    for (;;) {
        xTaskNotifyWait(pdFALSE,        // Don't clear bits on entry
                        0,              // Clear all bits on exit
                        &receivedValue, // Receives the notification value
                        portMAX_DELAY); // Wait indefinitely
        //echo recevied char
        cRxedChar = receivedValue & 0xFF;
        cliWrite((char *)&cRxedChar);
        if (cRxedChar == '\r' || cRxedChar == '\n')
        {
            // user pressed enter, process the command
            handleNewline(pcInputString, cOutputBuffer, &cInputIndex);
        }
        else
        {
            // user pressed a character add it to the input string
            handleCharacterInput(&cInputIndex, pcInputString);
        }
    }
}

void consolseTaskInit(void)
{
    HAL_UART_Receive_IT(&huart4, (uint8_t *)&huart4.Instance->RDR, 1);
    //start the command line task
    osThreadDef(cliTask, StartCliTask, osPriorityNormal, 0, configMINIMAL_STACK_SIZE * 4);
    cliTaskHandle = osThreadCreate(osThread(cliTask), NULL);
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if (huart == &huart4)
    {
        // grab char from data register
        char rxedValue = huart->Instance->RDR & 0xFF;
        // BaseType_t xHigherPriorityTaskWoken = pdFALSE;
        //get ready to receive another char
        HAL_UART_Receive_IT(huart, (uint8_t *)&huart->Instance->RDR, 1);
        //send the char to the command line task
        xTaskNotifyFromISR(cliTaskHandle, (uint32_t)rxedValue, eSetValueWithOverwrite , NULL);
        // portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
    }
}
