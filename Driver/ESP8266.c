 /**
 * @brief  ESP8266驱动
 * @param	void
 * @retval	void
 * @author ZCD
 * @Time 2021年1月24日
*/

#include "ESP8266.h"

uint16_t StringSecanPointer=0;
 /**
 * @brief  ESP8266发送函数
 * @param	指令1，指令2，指令1长度，指令2长度（实际发送为指令1+指令2；指令2为0则只发送指令1）
 * @retval	void
 * @author ZCD
 * @Time 2021年1月25日
*/
void Wifi_CMD_SEND(char *cmd,char* cmd2,uint8_t LenTemp,uint8_t LenTemp2)
{
	if(cmd2!=0)
	{
		HAL_UART_Transmit(&huart3,cmd,LenTemp-1,0x100);//sizeof计算的长度包括“\0”占位符要减掉
		HAL_UART_Transmit(&huart3,cmd2,LenTemp2,0x100);	
		HAL_UART_Transmit(&huart3,"\r\n",2,0x100);	
	}
	else
	{
		HAL_UART_Transmit(&huart3,cmd,LenTemp-1,0x100);//sizeof计算的长度包括“\0”占位符要减掉
		HAL_UART_Transmit(&huart3,"\r\n",2,0x100);		
	}
}
 /**
 * @brief  ESP8266初始化函数
 * @param	void
 * @retval	void
 * @author ZCD
 * @Time 2021年1月25日
*/
void Wifi_Init(void)//初始化
{
	Wifi_CMD_SEND(WifiRST,0,sizeof(WifiRST),2);
}
 /**
 * @brief  ESP8266设置模块工作模式函数
 * @param	 mode = 1-sta  2-ap  3-sta+ap
 * @retval	void
 * @author ZCD
 * @Time 2021年1月25日
*/
void Wifi_ModeSet(uint8_t mode)
{
	if(mode==1)
	{
		Wifi_CMD_SEND(WifiMODE,"1",sizeof(WifiMODE),1);	
	}
	if(mode==2)
	{
		Wifi_CMD_SEND(WifiMODE,"2",sizeof(WifiMODE),1);		
	}
	if(mode==3)
	{
		Wifi_CMD_SEND(WifiMODE,"3",sizeof(WifiMODE),1);		
	}

}
 /**
 * @brief  ESP8266连接路由器函数
 * @param	 SSID，密码
 * @retval	void
 * @author ZCD
 * @Time 2021年1月25日  没完成
*/
void Wifi_Connect_AP(char* SSID,char* PassWord)
{
	Wifi_CMD_SEND(WifiAPList,0,sizeof(WifiAPList),0);
}
 /**
 * @brief  检索特定字符串（最多检索四个特征字符）
 * @param	 检索特征字符，检索长度（<=4）
 * @retval	检索结果 1-是  0-否
 * @author ZCD
 * @Time 2021年1月26日
*/
uint8_t StringSearch(char *cha,uint8_t Len/*Len<=4*/)
{
	uint16_t CntMax=597;
	uint8_t CheckBuff[4]={0};
	
	for(uint16_t i=0;i<CntMax;i++)
	{
			uint8_t flag=1;
		CheckBuff[0]=Rx_Buff3[i];
		CheckBuff[1]=Rx_Buff3[i+1];
		CheckBuff[2]=Rx_Buff3[i+2];
		CheckBuff[3]=Rx_Buff3[i+3];	
		for(uint8_t j=0;j<Len;j++)
		{
			if(CheckBuff[j]!=cha[j])
			{
				flag=0;
			}
		}
		if(flag==1)
		{
			StringSecanPointer=i;
			return 1;
		}
	}

	return 0;
}
 /**
 * @brief  获取网络时间(时间来源为苏宁免费授时网页)
 * @param	 void
 * @retval	void
 * @author ZCD
 * @Time 2021年1月27日
*/
void Get_NETTime(void)
{
	Wifi_CMD_SEND(WifiBuildConnect,"\"TCP\",\"quan.suning.com\",80",sizeof(WifiBuildConnect),26);
	HAL_Delay(500);
	Wifi_CMD_SEND(WifiSendMODE,"1",sizeof(WifiSendMODE),1);
	HAL_Delay(500);
	Wifi_CMD_SEND(WifiSEND,0,sizeof(WifiSEND),0);
	HAL_Delay(500);
	uint8_t cha[]="GET http://quan.suning.com/getSysTime.do HTTP/1.1\r\nHost: quan.suning.com\r\n\r\n\r\n";
	HAL_UART_Transmit(&huart3,cha,sizeof(cha)-1,0x200);
	HAL_Delay(500);
	HAL_UART_Transmit(&huart3,"+++",3,0x100);	
	HAL_Delay(1000);
	
	if(StringSearch("ime1",4))
	{
		Time[2]=1+(Rx_Buff3[StringSecanPointer+19]-48)*10+Rx_Buff3[StringSecanPointer+20]-48;
		Time[1]=(Rx_Buff3[StringSecanPointer+17]-48)*10+Rx_Buff3[StringSecanPointer+18]-48;
		Time[0]=(Rx_Buff3[StringSecanPointer+15]-48)*10+Rx_Buff3[StringSecanPointer+16]-48;
		Day=(Rx_Buff3[StringSecanPointer+13]-48)*10+Rx_Buff3[StringSecanPointer+14]-48;
		Month=(Rx_Buff3[StringSecanPointer+11]-48)*10+Rx_Buff3[StringSecanPointer+12]-48;
		year=(Rx_Buff3[StringSecanPointer+7]-48)*1000+(Rx_Buff3[StringSecanPointer+8]-48)*100+(Rx_Buff3[StringSecanPointer+9]-48)*10+Rx_Buff3[StringSecanPointer+10]-48;
	}
}
//进程实体
void Wifi_Control(void const *argument)
{

	portTickType xLastWakeTime;
	xLastWakeTime = xTaskGetTickCount();

//-------------------------------------------------------//	
	
	HAL_Delay(1000);
	Wifi_Init();
	HAL_Delay(2000);
	uint8_t ConnectFlag=0;
	uint8_t TCPConFlag=0;
	for(;;)
	{	
		if(ConnectFlag==0)
		{
			ConnectFlag = StringSearch("GOT IP",4);
		}
		if(ConnectFlag==1)
		{
			if(TCPConFlag==0)
			{
				Get_NETTime();
				TCPConFlag=1;		
			}
		}
		
		
//-------------------------------------------------------//

//--------------------------------------------------------------------------------------------------------------------//		
		osDelayUntil(&xLastWakeTime,10/portTICK_RATE_MS);		
  }
}
//进程句柄
osThreadId Wifi_ControlHandle;
//进程创建声明
void Wifi_ControlThreadCreate(osPriority taskPriority)
{
	osThreadDef(Wifi_ControlThread,Wifi_Control,taskPriority,0,1024);
	Wifi_ControlHandle = osThreadCreate(osThread(Wifi_ControlThread),NULL);
}



