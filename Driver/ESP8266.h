 /**
 * @brief  ESP8266����
 * @param	void
 * @retval	void
 * @author ZCD
 * @Time 2021��1��24��
*/
#ifndef __ESP8266_H
#define __ESP8266_H

#include "usart.h"
#include "freertos.h"
#include "cmsis_os.h"
#include "Time_Soft.h"

#define WifiRST "AT+RST"//RST
#define WifiMODECheck "AT+CWMODE?"//�鿴����ģʽ
#define WifiMODE "AT+CWMODE="//1-STA  2-AP  3-AP+STA ���ù���ģʽ

#define WifiAPList "AT+CWLAP"//wifi�б� <ecn><ssid><rssi>
#define WifiJoinAP "AT+CWJAP="//����AP��AT+CWJAP="www.zniot.com","littlebee" ������littlebeeΪ���룩
#define WifiJoinAPSuces "AT+CWJAP?"//����ɹ���

#define WifiSetAP "AT+CWSAP="//����ap��AT+CWSAP=��ESP8266��,��12345678��,11,3��ssid,password,chl,ecn��
														 //chl-�ŵ��� ecn-���ܷ�ʽ 0-open 1-WEP 2-WPA_PSK 3-WPA2_PSK 4-WPA_WPA2_PSK
#define WifiIPList "AT+CWLIF"//�鿴�����豸��IP
#define WifiIPCheck "AT+CIFSR=?"//��ģ���Ƿ���IP
#define WifiIP "AT+CIFSR"//�鿴�Լ�IP��MAC   ��APģʽ�²����ã����ܵ���������

#define WifiNETSTA "AT+CIPSTA?"//������Ϣ ip ���� ��������
#define WifiMUX "AT+CIPMUX="//ģ������� 1-�� 0-��  AT+CIPMUX?�Ƿ���������
#define WifiBuildConnect "AT+CIPSTART="//��������  AT+CIPSTART=4,"TCP"," X1.X2.X3.X4",9999
																								 //AT+CIPSTART=4,"UDP","192.168.0.251",8080,1112,0  0��ʾ�̶�Զ�� 2��ʾԶ�˿ɱ�
#define WifiConnectList "AT+CIPSTATUS"//�鿴��ǰ���� ��id,type,addr,port,tetype��<tetype  0-cilent 1-server>

#define WifiSendMODE "AT+CIPMODE="//����ģʽ 1-͸�� 0��͸�� AT+CIPMODE? ��ѯ͸��ģʽ
#define WifiSEND "AT+CIPSEND"//͸������ 
#define WifiSENDLen "AT+CIPSEND="//�������� AT+CIPSEND=4,15

#define WifiTCPServer "AT+CIPSERVER="//AT+CIPSERVER=1,8888������1 Ϊ���� �����Ϊ0 ��ر� 8888��Ҫ�����˿ڣ�
#define WifiServerTime "AT+CIPSTO="//���÷���ʱʱ��  AT+CIPSTO����ѯ��ʱʱ��
#define WifiConnectClose "AT+CIPCLOSE="//AT+CIPCLOSE=4 �Ͽ��ĺ�����


void Wifi_CMD_SEND(char *cmd,char* cmd2,uint8_t LenTemp,uint8_t LenTemp2);
void Wifi_Init(void);
void Wifi_ControlThreadCreate(osPriority taskPriority);


#endif

