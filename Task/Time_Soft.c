 /**
 * @brief  软件计时
 * @param	void
 * @retval	void
 * @author ZCD
 * @Time 2021年1月23日
*/
#include "Time_Soft.h"


uint16_t TimeCnt=0;
uint8_t Time[3]={0};
uint8_t Day=23;
uint8_t Month=01;
uint16_t year=2021;

uint8_t time_cnt(void)
{
	TimeCnt++;
	if(TimeCnt==100)
	{
		Time[2]++;//秒
		TimeCnt=0;
	}
	if(Time[2]==60)
	{
		Time[1]++;//分
		Time[2]=0;

	}
	if(Time[1]==60)
	{
		Time[0]++;//时
		Time[1]=0;
	}
	if(Time[0]==24)
	{
		Day++;
		Time[0]=0;
	}
	return TimeCnt/100;//1s
}
//进程实体
void Time_Soft(void const *argument)
{

	portTickType xLastWakeTime;
	xLastWakeTime = xTaskGetTickCount();

//-------------------------------------------------------//	
	for(;;)
	{
		
		time_cnt();

//-------------------------------------------------------//


//--------------------------------------------------------------------------------------------------------------------//		
		osDelayUntil(&xLastWakeTime,10/portTICK_RATE_MS);		
  }
}
//进程句柄
osThreadId Time_SoftHandle;
//进程创建声明
void TIme_Soft_ThreadCreate(osPriority taskPriority)
{
	osThreadDef(Time_SoftThread,Time_Soft,taskPriority,0,128);
	Time_SoftHandle = osThreadCreate(osThread(Time_SoftThread),NULL);
}
