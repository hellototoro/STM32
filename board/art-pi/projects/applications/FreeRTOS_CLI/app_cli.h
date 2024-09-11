/*
 * app_cli.h
 *
 *  Created on: 2024年9月11日
 *      Author: huang jian
 */
#ifndef APP_CLI_H_
#define APP_CLI_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

// void processRxedChar(uint8_t rxChar);
// void handleNewline(const char *const pcInputString, char *cOutputBuffer, uint8_t *cInputIndex);
// void handleCharacterInput(uint8_t *cInputIndex, char *pcInputString);
// void vRegisterCLICommands(void);
// void vCommandConsoleTask(void *pvParameters);

void consolseTaskInit(void);

#ifdef __cplusplus
}
#endif

#endif /* APP_CLI_H_ */
