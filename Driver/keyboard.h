 /**
 * @brief  键盘驱动头文件
 * @param	void
 * @retval	void
 * @author ZCD
 * @Time 2021年1月18日
*/
#ifndef __keyboard_h
#define __keyboard_h

#include "stdint.h"
#include "gpio.h"
#include "freertos.h"
#include "cmsis_os.h"


void Key_Scan_ThreadCreate(osPriority taskPriority);
extern uint8_t keyInput[16];
extern uint8_t keyTrg[16];
//extern uint8_t key;
#endif

