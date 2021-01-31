 /**
 * @brief  ESP8266驱动
 * @param	void
 * @retval	void
 * @author ZCD
 * @Time 2021年1月24日
*/
#ifndef __ESP8266_H
#define __ESP8266_H

#include "usart.h"
#include "freertos.h"
#include "cmsis_os.h"
#include "Time_Soft.h"

#define WifiRST "AT+RST"//RST
#define WifiMODECheck "AT+CWMODE?"//查看工作模式
#define WifiMODE "AT+CWMODE="//1-STA  2-AP  3-AP+STA 设置工作模式

#define WifiAPList "AT+CWLAP"//wifi列表 <ecn><ssid><rssi>
#define WifiJoinAP "AT+CWJAP="//加入AP；AT+CWJAP="www.zniot.com","littlebee" （其中littlebee为密码）
#define WifiJoinAPSuces "AT+CWJAP?"//加入成功？

#define WifiSetAP "AT+CWSAP="//设置ap；AT+CWSAP=“ESP8266”,“12345678”,11,3（ssid,password,chl,ecn）
														 //chl-信道号 ecn-加密方式 0-open 1-WEP 2-WPA_PSK 3-WPA2_PSK 4-WPA_WPA2_PSK
#define WifiIPList "AT+CWLIF"//查看接入设备的IP
#define WifiIPCheck "AT+CIFSR=?"//查模块是否有IP
#define WifiIP "AT+CIFSR"//查看自己IP和MAC   （AP模式下不能用，可能导致死机）

#define WifiNETSTA "AT+CIPSTA?"//网络信息 ip 网关 子网掩码
#define WifiMUX "AT+CIPMUX="//模块多连接 1-是 0-否  AT+CIPMUX?是否建立多连接
#define WifiBuildConnect "AT+CIPSTART="//建立连接  AT+CIPSTART=4,"TCP"," X1.X2.X3.X4",9999
																								 //AT+CIPSTART=4,"UDP","192.168.0.251",8080,1112,0  0表示固定远端 2表示远端可变
#define WifiConnectList "AT+CIPSTATUS"//查看当前连接 （id,type,addr,port,tetype）<tetype  0-cilent 1-server>

#define WifiSendMODE "AT+CIPMODE="//发送模式 1-透传 0非透传 AT+CIPMODE? 查询透传模式
#define WifiSEND "AT+CIPSEND"//透传发送 
#define WifiSENDLen "AT+CIPSEND="//定长发送 AT+CIPSEND=4,15

#define WifiTCPServer "AT+CIPSERVER="//AT+CIPSERVER=1,8888（其中1 为开启 如果设为0 则关闭 8888：要监听端口）
#define WifiServerTime "AT+CIPSTO="//设置服务超时时间  AT+CIPSTO？查询超时时间
#define WifiConnectClose "AT+CIPCLOSE="//AT+CIPCLOSE=4 断开四号连接


void Wifi_CMD_SEND(char *cmd,char* cmd2,uint8_t LenTemp,uint8_t LenTemp2);
void Wifi_Init(void);
void Wifi_ControlThreadCreate(osPriority taskPriority);


#endif

