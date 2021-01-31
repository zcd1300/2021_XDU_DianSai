#ifndef __OLED_H
#define __OLED_H 

//#include "sys.h"
#include "stdlib.h"	
#include "i2c.h"

#include "bmp.h"


#define SSD1306Addr 0x78
#define WCom 0 
#define WData 0x40
#define OLED_CMD  0	//写命令
#define OLED_DATA 1	//写数据

/*
	0xAE			//--关闭显示
	0x00			//--起始列地址低四位 0x00~0x0f
	0x10			//--起始列地址高四位 0x10~0x1f
	
	0x40			//--设置起始行地址,设置映射RAM显示起始行0~63（0x40~0x7F）
	0xb0			//--设置起始GRAM页面寻址模式[2:0](b0-b7);
	
	0x81			//--设置对比度控制寄存器
	0xCF			//--1~255 ；默认0x7f
	
	0xA1			//--设置分段/列映射     0xa0左右反置 0xa1正常
	0xC8			//--设置COM/行扫描方向   0xc0上下反置 0xc8正常
	
	0xA8			//--设置芯片复用比（驱动路数）1~64
	0x3f			//--默认1/64 duty
	
	0xD3			//--设置显示偏移映射RAM计数器（0x00~0x3F）
	0x00			//--无偏移
	
	0xd5			//--设置显示时钟分频比/振荡器频率
	0x80			//--设置分频比，将时钟设置为100帧/秒
	
	0xD9			//--set pre-charge period预充电周期
	0xF1			//--Set Pre-Charge as 15 Clocks & Discharge as 1 Clock将预充电设置为15个时钟，放电设置为1个时钟
	
	0xDA			//--设置com引脚硬件配置
	0x12			//--默认[5:4]配置
	
	0xDB			//--set vcomh 电压倍率
	0x40			//Set VCOM Deselect Level
	
	0x20			//--设置页面寻址模式（0x00/0x01/0x02）
	0x02			//--默认0x20（01b列地址模式；10b 行地址模式）
	
	0x8D			//--电荷泵设置选中（两字节）
	0x14			//--设置bit2 为1开启（0x14）0关闭（0x10）
	
	0xA4			// 全局显示 bit0=1/0 (0xa4黑/0xa5白)
	0xA6			// 显示模式(0xa6正常/a7反相) 
	0xAF			//--开启显示
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


