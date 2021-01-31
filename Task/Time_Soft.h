 /**
 * @brief  �����ʱ
 * @param	void
 * @retval	void
 * @author ZCD
 * @Time 2021��1��23��
*/
#ifndef __Time_Soft_h
#define __Time_Soft_h

#include "stdint.h"
#include "freertos.h"
#include "cmsis_os.h"
#include "oled.h"

extern uint16_t TimeCnt;
extern uint8_t Time[3];
extern uint8_t Day;
extern uint8_t Month;
extern uint16_t year;

uint8_t time_cnt(void);
void TIme_Soft_ThreadCreate(osPriority taskPriority);

#endif

