 /**
 * @brief  0.96寸0led显示
 * @param	void
 * @retval	void
 * @author ZCD
 * @Time 2021年1月19日
*/
#include "oled096.h"
#include "setjmp.h"
#include "ESP8266.h"

float FrameRate=0;
uint8_t LightTime[2]={0};
uint8_t LightFlag[2]={0xdb,0};

 /**
 * @brief  显示功能1文本
 * @param	void
 * @retval	void
 * @author ZCD
 * @Time 2021年1月23日
*/
void text(void)
{
	OLED_ShowChinese(0,0,0,16);//西
	OLED_ShowChinese(16,0,1,16);//安		
	OLED_ShowChinese(32,0,2,16);//电
	OLED_ShowChinese(48,0,3,16);//子
	OLED_ShowChinese(64,0,4,16);//科
	OLED_ShowChinese(80,0,5,16);//技
	OLED_ShowChinese(96,0,6,16);//大
	OLED_ShowChinese(112,0,7,16);//学
	OLED_ShowNum(8,16,2021,4,16);//2121
	OLED_ShowChinese(84,16,8,16);//电
	OLED_ShowChinese(100,16,9,16);//赛	
}
 /**
 * @brief  控制校徽图片移动
 * @param	void
 * @retval	void
 * @author ZCD
 * @Time 2021年1月23日
*/
	uint8_t x=39;
	uint8_t y=18;
	jmp_buf evn;
void XY_Move_test()
{

		if(keyInput[9]==1)
		{
			
			if(y>0)
			{
				y=y-1;
			}
		}
		if(keyInput[11]==1)
		{
			if(y<63)
			{
				y=y+1;
			}
		}
		if(keyInput[14]==1)
		{
			
			if(x>0)
			{
				x=x-1;
			}
		}
		if(keyInput[6]==1)
		{
			if(x<128-45)
			{
				x=x+1;
			}
		}		
		if(keyInput[10]==1)
			{
				longjmp(evn,1);
			}
}
 /**
 * @brief  键盘控制逻辑
 * @param	void
 * @retval	void
 * @author ZCD
 * @Time 2021年1月23日
*/
uint8_t Fun1Flag=0;
uint8_t Fun2Flag=1;
uint8_t Fun3Flag=0;
uint8_t LightStamp=0;
void Key_Ctrl(void)
{
	uint8_t X1=8;
	uint8_t X2=24;
	uint8_t X3=24;
	if(keyInput[12]==1)
	{
		Fun1Flag=1;
		Fun2Flag=0;
		Fun3Flag=0;
		LightStamp=0;
	}
	if(keyInput[8]==1)
	{
		Fun1Flag=0;
		Fun2Flag=1;
		Fun3Flag=0;
		LightStamp=0;
	}
	if(keyInput[4]==1)
	{
		if(LightStamp==0)
		{
			for(uint8_t i=0;i<16;i++)
			{keyTrg[i]=0;}
			LightStamp=1;
		}		
		Fun1Flag=0;
		Fun2Flag=0;
		Fun3Flag=1;
	}
	if(Fun1Flag==1)//功能1（文字）
	{
		XY_Move_test();		
		OLED_ShowPicture(x,y,x+45,270,xiaohui);
		text();	
	}
	if(Fun2Flag==1)//功能2（时间）
	{

		OLED_ShowNum(X1,16,year,4,16);//2121
		OLED_ShowChinese(X1+32,16,10,16);//年
		OLED_ShowNum(X1+48,16,Month,2,16);//01		
		OLED_ShowChinese(X1+64,16,11,16);//月
		OLED_ShowNum(X1+80,16,Day,2,16);//01				
		OLED_ShowChinese(X1+96,16,12,16);//日
		
		OLED_ShowNum(X2,32,Time[0],2,16);//时
		OLED_ShowChinese(X2+16,32,13,16);//:
		OLED_ShowNum(X2+32,32,Time[1],2,16);//分				
		OLED_ShowChinese(X2+48,32,13,16);//:		
		OLED_ShowNum(X2+64,32,Time[2],2,16);//秒				
	}
	if(Fun3Flag==1)//功能3（流水灯）
	{	

		
		OLED_ShowString(X3,16,"L1",16);
		OLED_ShowString(X3+32,16,"L2",16);
		OLED_ShowString(X3+64,16,"L3",16);
		OLED_ShowPicture(X3,40,X3+16,32,LEDLight_OFF);
		OLED_ShowPicture(X3+32,40,X3+48,32,LEDLight_OFF);
		OLED_ShowPicture(X3+64,40,X3+80,32,LEDLight_OFF);	
		if(keyTrg[13]==1)
		{//1s双灯流水

			if(LightFlag[0]<0x6)
			{LightFlag[0]=0xdb;}			
			LightFlag[0]=LightFlag[0]>>LightTime[1]/2;
			if((LightFlag[0]&0x1)==1)
			{
				OLED_ShowPicture(X3,40,X3+16,32,LEDLight_ON);					
			}
			else
			{
				OLED_ShowPicture(X3,40,X3+16,32,LEDLight_OFF);
			}
			if((LightFlag[0]&0x02)==0x2)
			{
				OLED_ShowPicture(X3+32,40,X3+48,32,LEDLight_ON);				
			}
			else
			{
				OLED_ShowPicture(X3+32,40,X3+48,32,LEDLight_OFF);
			}
			if((LightFlag[0]&0x04)==0x4)
			{
				OLED_ShowPicture(X3+64,40,X3+80,32,LEDLight_ON);			
			}
			else
			{
				OLED_ShowPicture(X3+64,40,X3+80,32,LEDLight_OFF);
			}			
		}
		else if(keyTrg[9]==1)
		{//0.5s单流水

			if(LightTime[0]==5||LightTime[0]==10)
			{
				LightFlag[1]++;
			}
			if(LightFlag[1]==1)
			{
				OLED_ShowPicture(X3,40,X3+16,32,LEDLight_ON);
				OLED_ShowPicture(X3+32,40,X3+48,32,LEDLight_OFF);
				OLED_ShowPicture(X3+64,40,X3+80,32,LEDLight_OFF);					
			}
			if(LightFlag[1]==2)
			{
				OLED_ShowPicture(X3,40,X3+16,32,LEDLight_OFF);
				OLED_ShowPicture(X3+32,40,X3+48,32,LEDLight_ON);
				OLED_ShowPicture(X3+64,40,X3+80,32,LEDLight_OFF);				
			}
			if(LightFlag[1]==3)
			{
				OLED_ShowPicture(X3,40,X3+16,32,LEDLight_OFF);
				OLED_ShowPicture(X3+32,40,X3+48,32,LEDLight_OFF);
				OLED_ShowPicture(X3+64,40,X3+80,32,LEDLight_ON);	
			}
			if(LightFlag[1]>3)
			{
					LightFlag[1]=1;		
			}
		}
		else
		{//单独控制灯

			if(keyTrg[14]==1)
			{
				OLED_ShowPicture(X3,40,X3+16,32,LEDLight_ON);				
			}
			if(keyTrg[10]==1)
			{
				OLED_ShowPicture(X3+32,40,X3+48,32,LEDLight_ON);
			}
			if(keyTrg[6]==1)
			{
				OLED_ShowPicture(X3+64,40,X3+80,32,LEDLight_ON);
			}
		}
	}
}
uint8_t bright[2]={0x81,0x0f};
void bright_ctrol(void)
{
	if(keyInput[0]==1)
	{
		if(bright[1]<255)
		{
			bright[1]++;
			OLED_ShowNum(17,50,bright[1],3,12);			
		}
		else
		{
			OLED_ShowPicture(0,50,16,32,LEDLight_ON);	
			OLED_ShowNum(17,50,bright[1],3,12);					
		}
		OLED_WR(bright,2,OLED_CMD);
	}
	if(keyInput[1]==1)
	{
		if(bright[1]>0)
		{
			bright[1]--;
			OLED_ShowNum(17,50,bright[1],3,12);			
		}
		else
		{
			OLED_ShowPicture(0,50,16,32,LEDLight_OFF);	
			OLED_ShowNum(17,50,bright[1],3,12);					
		}		
		OLED_WR(bright,2,OLED_CMD);	
	}

}
void SEG_Tag(void)
{
		OLED_GRAM[7][127]=0xff;
		OLED_GRAM[6][0]=0xff;
		OLED_GRAM[5][127]=0xff;
		OLED_GRAM[4][127]=0xff;
		OLED_GRAM[3][0]=0xff;
		OLED_GRAM[2][127]=0xff;
		OLED_GRAM[1][0]=0xff;
		OLED_GRAM[0][127]=0xff;		
}
//进程实体
void OLED_Control(void const *argument)
{

	portTickType xLastWakeTime;
	xLastWakeTime = xTaskGetTickCount();

	osDelay(500);	
	OLED_Init();
	OLED_Refresh();
	setjmp(evn);	
//-------------------------------------------------------//	

	x=39;
	y=18;
	for(;;)
	{
		OLED_Clear_Soft();
		
		LightTime[0]++;
		LightTime[1]=LightTime[0]/5;//0.5s时间戳(0-1-2)
		if(LightTime[0]>10)
		{LightTime[0]=0;}	
//-------------------------------------------------------//
		Key_Ctrl();

		for(uint8_t i=0;i<5;i++)
		{
			bright_ctrol();		
		}
//-------------------------------------------------------//		
		//SEG_Tag();
		OLED_Refresh();
		FrameRate=FrameCnt*100;
		FrameCnt=0;
//--------------------------------------------------------------------------------------------------------------------//		
		osDelayUntil(&xLastWakeTime,100/portTICK_RATE_MS);		
  }
}
//进程句柄
osThreadId OLED_ControlHandle;
//进程创建声明
void OLED_Ctrl_ThreadCreate(osPriority taskPriority)
{
	osThreadDef(OLED_CtrlThread,OLED_Control,taskPriority,0,256);
	OLED_ControlHandle = osThreadCreate(osThread(OLED_CtrlThread),NULL);
}

