 /**
 * @brief  0.96寸0led显示
 * @param	void
 * @retval	void
 * @author ZCD
 * @Time 2021年1月19日
*/
#ifndef __oled096_h
#define __oled096_h

#include "stdint.h"
#include "gpio.h"
#include "freertos.h"
#include "cmsis_os.h"
#include "i2c.h"
#include "oled.h"
#include "keyboard.h"
#include "Time_Soft.h"
void OLED_Ctrl_ThreadCreate(osPriority taskPriority);


#endif

