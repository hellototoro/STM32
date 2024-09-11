/*
 * cli_commands.c
 *
 *  Created on: 2024年9月11日
 *      Author: huang jian
 */
#include <stdio.h>
#include <stdlib.h>

#include "cli_commands.h"
#include "cmsis_os.h"
#include "FreeRTOS_CLI.h"

static BaseType_t cmd_clearScreen(char *pcWriteBuffer, size_t xWriteBufferLen,
                                  const char *pcCommandString)
{
    /* Remove compile time warnings about unused parameters, and check the
	write buffer is not NULL.  NOTE - for simplicity, this example assumes the
	write buffer length is adequate, so does not check for buffer overflows. */
    (void)pcCommandString;
    (void)xWriteBufferLen;
    memset(pcWriteBuffer, 0x00, xWriteBufferLen);
    printf("\033[2J\033[1;1H");
    return pdFALSE;
}

static BaseType_t cmd_toggle_led(char *pcWriteBuffer, size_t xWriteBufferLen,
                                 const char *pcCommandString)
{
    (void)pcCommandString; // comntains the command string
    (void)xWriteBufferLen; // contains the length of the write buffer
    
    /* Toggle the LED */
    HAL_GPIO_TogglePin(LED_BLUE_GPIO_Port, LED_BLUE_Pin); // implement your code to toggle led
    
    /* Write the response to the buffer */
    uint8_t string[] = "LED toggled\r\n";
    strcpy(pcWriteBuffer, (char *)string);
    
    return pdFALSE; // no more string output is needed
}

static BaseType_t cmd_add(char *pcWriteBuffer, size_t xWriteBufferLen,
                                 const char *pcCommandString)
{
    UNUSED(xWriteBufferLen);
    // hold pointer to parameter string
    const char *pcParameter1, *pcParameter2;
    BaseType_t xParameter1StringLength, xParameter2StringLength;

    pcParameter1 = FreeRTOS_CLIGetParameter
                        (
                          /* The command string itself. */
                          pcCommandString,
                          /* Return the first parameter. */
                          1,
                          /* Store the parameter string length. */
                          &xParameter1StringLength
                        );
    pcParameter2 = FreeRTOS_CLIGetParameter
                        (
                          /* The command string itself. */
                          pcCommandString,
                          /* Return the first parameter. */
                          2,
                          /* Store the parameter string length. */
                          &xParameter2StringLength
                        );
    // convert the string to a number
    int32_t xValue1 = strtol(pcParameter1, NULL, 10);
    int32_t xValue2 = strtol(pcParameter2, NULL, 10);
    // add the two numbers
    int32_t xResultValue = xValue1 + xValue2;
    // convert the result to a string
    char cResultString[10];
    itoa(xResultValue, cResultString, 10);
    // copy the result to the write buffer
    strcpy(pcWriteBuffer, cResultString);
    
    return pdFALSE;
}

static const CLI_Command_Definition_t xCommandList[] = {
    {
        .pcCommand = "cls", /* The command string to type. */
        .pcHelpString = "cls:\r\n Clears screen\r\n\r\n",
        .pxCommandInterpreter = cmd_clearScreen, /* The function to run. */
        .cExpectedNumberOfParameters = 0 /* No parameters are expected. */
    },
    {
        .pcCommand = "toggleled", /* The command string to type. */
        .pcHelpString = "toggleled n:\r\n toggles led n amount of times\r\n\r\n",
        .pxCommandInterpreter = cmd_toggle_led, /* The function to run. */
        .cExpectedNumberOfParameters = 1 /* No parameters are expected. */
    },
    {
        .pcCommand = "add", /* The command string to type. */
        .pcHelpString = "add a b:\r\n add two numbers\r\n\r\n",
        .pxCommandInterpreter = cmd_add, /* The function to run. */
        .cExpectedNumberOfParameters = 2 /* No parameters are expected. */
    },
    {
        .pcCommand = NULL /* simply used as delimeter for end of array*/
    }
};

void vRegisterCLICommands(void)
{
    //itterate thourgh the list of commands and register them
    for (int i = 0; xCommandList[i].pcCommand != NULL; i++)
    {
        FreeRTOS_CLIRegisterCommand(&xCommandList[i]);
    }
}
