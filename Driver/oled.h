#ifndef __OLED_H
#define __OLED_H 

//#include "sys.h"
#include "stdlib.h"	
#include "i2c.h"

#include "bmp.h"


#define SSD1306Addr 0x78
#define WCom 0 
#define WData 0x40
#define OLED_CMD  0	//д����
#define OLED_DATA 1	//д����

/*
	0xAE			//--�ر���ʾ
	0x00			//--��ʼ�е�ַ����λ 0x00~0x0f
	0x10			//--��ʼ�е�ַ����λ 0x10~0x1f
	
	0x40			//--������ʼ�е�ַ,����ӳ��RAM��ʾ��ʼ��0~63��0x40~0x7F��
	0xb0			//--������ʼGRAMҳ��Ѱַģʽ[2:0](b0-b7);
	
	0x81			//--���öԱȶȿ��ƼĴ���
	0xCF			//--1~255 ��Ĭ��0x7f
	
	0xA1			//--���÷ֶ�/��ӳ��     0xa0���ҷ��� 0xa1����
	0xC8			//--����COM/��ɨ�跽��   0xc0���·��� 0xc8����
	
	0xA8			//--����оƬ���ñȣ�����·����1~64
	0x3f			//--Ĭ��1/64 duty
	
	0xD3			//--������ʾƫ��ӳ��RAM��������0x00~0x3F��
	0x00			//--��ƫ��
	
	0xd5			//--������ʾʱ�ӷ�Ƶ��/����Ƶ��
	0x80			//--���÷�Ƶ�ȣ���ʱ������Ϊ100֡/��
	
	0xD9			//--set pre-charge periodԤ�������
	0xF1			//--Set Pre-Charge as 15 Clocks & Discharge as 1 Clock��Ԥ�������Ϊ15��ʱ�ӣ��ŵ�����Ϊ1��ʱ��
	
	0xDA			//--����com����Ӳ������
	0x12			//--Ĭ��[5:4]����
	
	0xDB			//--set vcomh ��ѹ����
	0x40			//Set VCOM Deselect Level
	
	0x20			//--����ҳ��Ѱַģʽ��0x00/0x01/0x02��
	0x02			//--Ĭ��0x20��01b�е�ַģʽ��10b �е�ַģʽ��
	
	0x8D			//--��ɱ�����ѡ�У����ֽڣ�
	0x14			//--����bit2 Ϊ1������0x14��0�رգ�0x10��
	
	0xA4			// ȫ����ʾ bit0=1/0 (0xa4��/0xa5��)
	0xA6			// ��ʾģʽ(0xa6����/a7����) 
	0xAF			//--������ʾ
*/
#define aaa 8
#define bbb 128

extern uint8_t OLED_GRAM[aaa][bbb];
extern uint16_t FrameCnt;

void OLED_WR(uint8_t *data,uint16_t num,uint8_t mode);
void OLED_ClearPoint(uint8_t x,uint8_t y);
void OLED_ColorTurn(uint8_t i);
void OLED_DisplayTurn(uint8_t i);
void OLED_DisPlay_On(void);
void OLED_DisPlay_Off(void);
void OLED_Refresh(void);
void OLED_Clear_Hard(void);
void OLED_Clear_Soft(void);
void OLED_DrawPoint(uint8_t x,uint8_t y);
void OLED_DrawLine(uint8_t x1,uint8_t y1,uint8_t x2,uint8_t y2);
void OLED_DrawCircle(uint8_t x,uint8_t y,uint8_t r);
void OLED_ShowChar(uint8_t x,uint8_t y,uint8_t chr,uint8_t size1);
void OLED_ShowString(uint8_t x,uint8_t y,uint8_t *chr,uint8_t size1);
void OLED_ShowNum(uint8_t x,uint8_t y,uint32_t num,uint8_t len,uint8_t size1);
void OLED_ShowChinese(uint8_t x,uint8_t y,uint8_t num,uint8_t size1);

uint8_t OLED_WR_BP(uint8_t y,uint8_t Data,uint8_t Data2);
void OLED_ShowPicture(uint8_t x0,uint8_t y0,uint8_t x1,uint16_t Len,const uint8_t BMP[]);
void OLED_Init(void);

#endif


