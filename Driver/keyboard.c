 /**
 * @brief  键盘驱动
 * @param	void
 * @retval	void
 * @author ZCD
 * @Time 2021年1月18日
*/

#include "keyboard.h"

//uint8_t key =255;//单个按键有没有按下，1~16表示不同按键，不支持检测多个按键同时按下
uint8_t keyInput[16]={0};//数组的每个表示不同按键，0为没按下1为按下，支持多个按键同时检测，但是相比单个按键检测周期更长，延迟更大
uint8_t keyTrg[16]={0};
uint32_t temp=0;
	
	
 /**
 * @brief  键盘扫描——单个按键
 * @param	void
 * @retval	void
 * @author ZCD
 * @Time 2021年1月19日
*/	
/*uint8_t key_scan_single(void)
{
	uint8_t back=254;
//	for(uint8_t i=0;i<16;i++)
//	{
//		keyInput[i]=0;
//	}
//	uint8_t cnt_x =4;
//----------------第一行------------------//
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3,GPIO_PIN_RESET);//重置行引脚
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_3,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2,GPIO_PIN_SET);	
	if((GPIOA->IDR & 0xf0)!= 0xf0)
	{
		HAL_Delay(4);
		if((GPIOA->IDR & 0xf0) != 0xf0)
		{
			temp = (GPIOA->IDR &0xf7);
			switch(temp)
			{
				case 0xe7:
					back =1;
					keyInput[0]=1;
					break;
				case 0xd7:
					back=2;
					keyInput[1]=1;
					break;
				case 0xb7:
					back=3;
					keyInput[2]=1;
					break;
				case 0x77:
					back=4;
					keyInput[3]=1;
					break;
				default :
					back =255;		
			}		
		}
	}
	
//----------------第二行------------------//	
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3,GPIO_PIN_RESET);//重置行引脚
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_2,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_3,GPIO_PIN_SET);	
	if((GPIOA->IDR & 0xf0)!= 0xf0)
	{
		HAL_Delay(4);
		if((GPIOA->IDR & 0xf0) != 0xf0)
		{
			temp = (GPIOA->IDR &0xfb);
			switch(temp)
			{
				case 0xeb:
					back =5;
					keyInput[4]=1;
					break;
				case 0xdb:
					back=6;
					keyInput[5]=1;
					break;
				case 0xbb:
					back=7;
					keyInput[6]=1;
					break;
				case 0x7b:
					back=8;
					keyInput[7]=1;
					break;
				default :back =255;
			}		
		}
	}

//----------------第三行------------------//	
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3,GPIO_PIN_RESET);//重置行引脚
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_1,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_0|GPIO_PIN_3|GPIO_PIN_2,GPIO_PIN_SET);	
	if((GPIOA->IDR & 0xf0)!= 0xf0)
	{
		HAL_Delay(4);
		if((GPIOA->IDR & 0xf0) != 0xf0)
		{
			temp = (GPIOA->IDR &0xfd);
			switch(temp)
			{
				case 0xed:
					back =9;
					keyInput[8]=1;
					break;
				case 0xdd:
					back=10;
					keyInput[9]=1;
					break;
				case 0xbd:
					back=11;
					keyInput[10]=1;
					break;
				case 0x7d:
					back=12;
					keyInput[11]=1;
					break;
				default :back =255;
			}		
		}
	}

//----------------第四行------------------//
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3,GPIO_PIN_RESET);//重置行引脚
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_0,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_3|GPIO_PIN_1|GPIO_PIN_2,GPIO_PIN_SET);	
	if((GPIOA->IDR & 0xf0)!= 0xf0)
	{
		HAL_Delay(4);
		if((GPIOA->IDR & 0xf0) != 0xf0)
		{
			temp = (GPIOA->IDR &0xfe);
			switch(temp)
			{
				case 0xee:
					back =13;
					keyInput[12]=1;
					break;
				case 0xde:
					back=14;
					keyInput[13]=1;
					break;
				case 0xbe:
					back=15;
					keyInput[14]=1;
					break;
				case 0x7e:
					back=16;
					keyInput[15]=1;
					break;
				default :back =255;
			}		
		}
	}
	
	
 return back;
}*/

 /**
 * @brief  键盘扫描——指定按键;
 * @param	uint8_t num 要扫描的按键号（4*4键盘）
 * @retval	void
 * @author ZCD
 * @Time 2021年1月29日
*/
void Key_Scan_Specific(uint8_t num)
{
	temp=0;

	if(num<=4)//第一行
	{
		HAL_GPIO_WritePin(GPIOA,GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3,GPIO_PIN_RESET);//重置行引脚
		HAL_GPIO_WritePin(GPIOA,GPIO_PIN_3,GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA,GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2,GPIO_PIN_RESET);		
		if((GPIOA->IDR & 0xf0)!= 0x00)
		{
			HAL_Delay(4);//消抖
			if((GPIOA->IDR & 0xf0) != 0x00)
			{
				temp = (GPIOA->IDR &0xf8);
				if(num==1)
				{
					if(((temp>>4)&0x1)==1)
					{	keyInput[0]=1;}
				}
				if(num==2)
				{
					if(((temp>>5)&0x1)==1)
					{	keyInput[1]=1;}
			
				}
				if(num==3)
				{
					if(((temp>>6)&0x1)==1)
					{	keyInput[2]=1;}

				}
				if(num==4)
				{
					if(((temp>>7)&0x1)==1)
					{	keyInput[3]=1;}
				}				
			}
		}
		else
		{
			keyInput[num-1]=0;
		}
	}
	else if(num<=8)//第二行
	{
		HAL_GPIO_WritePin(GPIOA,GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3,GPIO_PIN_RESET);//重置行引脚
		HAL_GPIO_WritePin(GPIOA,GPIO_PIN_2,GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA,GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_3,GPIO_PIN_RESET);	
		if((GPIOA->IDR & 0xf0)!= 0x00)
		{
			HAL_Delay(4);
			if((GPIOA->IDR & 0xf0) != 0x00)
			{
				temp = (GPIOA->IDR &0xf4);
				if(num==5)
				{
					if(((temp>>4)&0x1)==1)
					{	keyInput[4]=1;}
				}
				if(num==6)
				{
					if(((temp>>5)&0x1)==1)
					{	keyInput[5]=1;}
				}
				if(num==7)
				{
					if(((temp>>6)&0x1)==1)
					{	keyInput[6]=1;}
				}
				if(num==8)
				{
					if(((temp>>7)&0x1)==1)
					{	keyInput[7]=1;}
				}					
			}
		}	
		else
		{
			keyInput[num-1]=0;
		}
	}
	else if(num<=12)//第三行
	{
		HAL_GPIO_WritePin(GPIOA,GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3,GPIO_PIN_RESET);//重置行引脚
		HAL_GPIO_WritePin(GPIOA,GPIO_PIN_1,GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA,GPIO_PIN_0|GPIO_PIN_3|GPIO_PIN_2,GPIO_PIN_RESET);	
		if((GPIOA->IDR & 0xf0)!= 0x00)
		{
			HAL_Delay(4);
			if((GPIOA->IDR & 0xf0) != 0x00)
			{
				temp = (GPIOA->IDR &0xf2);
				if(num==9)
				{
					if(((temp>>4)&0x1)==1)
					{	keyInput[8]=1;}
				}
				if(num==10)
				{
					if(((temp>>5)&0x1)==1)
					{	keyInput[9]=1;}
				}
				if(num==11)
				{
					if(((temp>>6)&0x1)==1)
					{	keyInput[10]=1;}
				}
				if(num==12)
				{
					if(((temp>>7)&0x1)==1)
					{	keyInput[11]=1;}
				}					
			}
		}
		else
		{
			keyInput[num-1]=0;
		}		
	}
	else if(num<=16)//第四行
	{
		HAL_GPIO_WritePin(GPIOA,GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3,GPIO_PIN_RESET);//重置行引脚
		HAL_GPIO_WritePin(GPIOA,GPIO_PIN_0,GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA,GPIO_PIN_3|GPIO_PIN_1|GPIO_PIN_2,GPIO_PIN_RESET);	
		if((GPIOA->IDR & 0xf0)!= 0x00)
		{
			HAL_Delay(4);
			if((GPIOA->IDR & 0xf0) != 0x00)
			{
				temp = (GPIOA->IDR &0xf1);
				if(num==13)
				{
					if(((temp>>4)&0x1)==1)
					{	keyInput[12]=1;}
				}
				if(num==14)
				{
					if(((temp>>5)&0x1)==1)
					{	keyInput[13]=1;}
				}
				if(num==15)
				{
					if(((temp>>6)&0x1)==1)
					{	keyInput[14]=1;}
				}
				if(num==16)
				{
					if(((temp>>7)&0x1)==1)
					{	keyInput[15]=1;}
				}		
			}
		}
		else
		{
			keyInput[num-1]=0;
		}
	}
	else
	{/**/	}
}
 /**
 * @brief  键盘单击检查
 * @param	void
 * @retval	void
 * @author ZCD
 * @Time 2021年1月23日
*/
uint8_t keyResetFlag[16]={0};
void Key_Click_Single(void)
{
	for(uint8_t i=0;i<16;i++)
	{
		if(keyInput[i]==1&&keyResetFlag[i]==0)
		{
			keyTrg[i] = ~keyTrg[i]&0x1;
			keyResetFlag[i]=1;
		}
		else if(keyInput[i]==0)
		{
			keyResetFlag[i]=0;
		}
	}
}
 /**
 * @brief  键盘扫描——指定范围的多个;也可以只扫描一个
 * @param	uint8_t start,uint8_t end;扫描起始按键，扫描结束按键（4*4键盘最大范围start=1，end=16）
 * @retval	void
 * @author ZCD
 * @Time 2021年1月28日
*/
void Key_Scan_Mul(uint8_t start,uint8_t end)
{	
	uint8_t i=0;			
	for(i=start;i<=end;i++)
	{
		Key_Scan_Specific(i);
	}
}
//进程实体
void Keyboard_Scan(void const *argument)
{
	portTickType xLastWakeTime;
	xLastWakeTime = xTaskGetTickCount();

	for(;;)
	{

		Key_Scan_Mul(1,16);	
		Key_Click_Single();
		osDelayUntil(&xLastWakeTime,1/portTICK_RATE_MS);		
	}

}
//进程句柄
osThreadId keyboard_ScanHandle;
//进程创建声明
void Key_Scan_ThreadCreate(osPriority taskPriority)
{
	osThreadDef(key_ScanThread,Keyboard_Scan,taskPriority,0,128);
	keyboard_ScanHandle = osThreadCreate(osThread(key_ScanThread),NULL);
}
