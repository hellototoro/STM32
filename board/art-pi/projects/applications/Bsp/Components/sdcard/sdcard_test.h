/*
 * sdcard_test.h
 *
 *  Created on: 2024年8月21日
 *      Author: huang
 */

#ifndef __SDCARD_TEST_H_
#define __SDCARD_TEST_H_

#define SD_TIMEOUT             ((uint32_t)0x00100000U)
//块的大小（以字节为单位）
#define BLOCK_SIZE            512 
//块的数目
#define NUMBER_OF_BLOCKS      10
//块的数据大小
#define MULTI_BUFFER_SIZE    (BLOCK_SIZE * NUMBER_OF_BLOCKS)

void sdcard_test(void);

#endif /* __SDCARD_TEST_H_ */
