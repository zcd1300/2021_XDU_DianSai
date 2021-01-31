#include "oled.h"
#include "stdlib.h"
#include "oledfont.h"  	 

uint16_t FrameCnt=0;
uint8_t OLED_GRAM[aaa][bbb]={0};

uint8_t InitD[]={0xae, 0x20, 0x10, 0xb0, 0xc8, 0x00, 0x10, 0x40, 0x81, 0x0f/*Light*/, 0xa1, 0xa6, 0xa8, 0x3f, 0xa4, 0xd3, 0, 0xd5, 0xf0, 0xd9, 0x22, 0xda, 0x12, 0xdb, 0x20, 0x8d, 0x14, 0xaf};
uint8_t OriginD[]={0xb0, 0x00, 0x10};

//连续写入多位内容
//向SSD1306写入多个字节。
//mode:数据/命令标志 0,表示命令;1,表示数据;
void OLED_WR(uint8_t *data,uint16_t num,uint8_t mode)//mode=0--cmd;mode=1--data
{
	if(mode)//data
	{
		HAL_I2C_Mem_Write(&hi2c1,0x78,0x40,8,data,num,0x100);
	}
  else//cmd
	{
		HAL_I2C_Mem_Write(&hi2c1,0x78,0x00,8,data,num,0x100);
	}

}
//更新显存到OLED内部BUf	
void OLED_Refresh(void)
{
//	uint8_t temp[3]={0xb0,0x00,0x10};//(设置行起始页地址,设置低列起始地址,设置高列起始地址)
//	for(i=0;i<8;i++)
//	{
//	   OLED_WR(temp,3,OLED_CMD); //写入命令（分页写入）
//		 temp[0]=0xb0+1;

//     HAL_I2C_Mem_Write(&hi2c1, SSD1306Addr, WData, I2C_MEMADD_SIZE_8BIT, &OLED_GRAM[i][0], 128, 1000);
//  }
  for(uint8_t i=0; i<aaa; ++i)
	{		
		HAL_I2C_Mem_Write(&hi2c1, SSD1306Addr, WData, I2C_MEMADD_SIZE_8BIT, &OLED_GRAM[i][0], 128, 100);
	}
	FrameCnt=FrameCnt+1;
}
//反显函数
void OLED_ColorTurn(uint8_t i)
{
	uint8_t temp[2]={0xa6,0xa7};
	if(i==0)
		{

			HAL_I2C_Mem_Write(&hi2c1, SSD1306Addr, WCom, I2C_MEMADD_SIZE_8BIT,  temp, 1, 100);//正常显示
		}
	if(i==1)
		{

			HAL_I2C_Mem_Write(&hi2c1, SSD1306Addr, WCom, I2C_MEMADD_SIZE_8BIT,  &temp[1], 1, 100);//反色显示
		}
}

//屏幕旋转180度
void OLED_DisplayTurn(uint8_t i)
{
	uint8_t temp[4]={0xc8,0xa1,0xc0,0xa0};
	if(i==0)
		{
			OLED_WR(temp,2,OLED_CMD);//正常显示

		}
	if(i==1)
		{
			OLED_WR(&temp[2],2,OLED_CMD);//反转显示
			
		}
}

//OLED显示开关 (1开/0关)
void OLED_DisPlay_Ctrl(uint8_t ctr)
{
	uint8_t temp[3]={0x8d,0x14,0xaf};//(电荷泵使能,开启电荷泵/0x10关闭,点亮屏幕)
	if(ctr==1)
	{
		OLED_WR(temp,3,OLED_CMD);//on
	}
	else
	{
		temp[1]=0x10;
		OLED_WR(temp,3,OLED_CMD);
	}
}



//清屏函数
void OLED_Clear_Hard(void)
{
	uint8_t i,n;
	for(i=0;i<bbb;i++)
	{
	   for(n=0;n<aaa;n++)
			{
			 OLED_GRAM[n][i]=0;//清除所有数据
			}
  }
	OLED_Refresh();//更新显示
}
void OLED_Clear_Soft(void)
{
	uint8_t i,n;
	for(i=0;i<bbb;i++)
	{
	   for(n=0;n<aaa;n++)
			{
			 OLED_GRAM[n][i]=0;//清除所有数据
			}
  }
}

//画点 
//x:0~127
//y:0~63
void OLED_DrawPoint(uint8_t x,uint8_t y)
{
	uint8_t i,m,n;
	i=y/8;
	m=y%8;
	n=1<<m;
	OLED_GRAM[i][x]|=n;
}

//清除一个点
//x:0~127
//y:0~63
void OLED_ClearPoint(uint8_t x,uint8_t y)
{
	uint8_t i,m,n;
	i=y/8;
	m=y%8;
	n=1<<m;
	OLED_GRAM[i][x]=~OLED_GRAM[i][x];
	OLED_GRAM[i][x]|=n;
	OLED_GRAM[i][x]=~OLED_GRAM[i][x];
}


//画线
//x:0~128
//y:0~64
void OLED_DrawLine(uint8_t x1,uint8_t y1,uint8_t x2,uint8_t y2)
{
	uint8_t i,k,k1,k2;//,y0;
	if((x1<0)||(x2>128)||(y1<0)||(y2>64)||(x1>x2)||(y1>y2))
	{
		return;
	}
	if(x1==x2)    //画竖线
	{
			for(i=0;i<(y2-y1);i++)
			{
				OLED_DrawPoint(x1,y1+i);
			}
  }
	else if(y1==y2)   //画横线
	{
			for(i=0;i<(x2-x1);i++)
			{
				OLED_DrawPoint(x1+i,y1);
			}
  }
	else      //画斜线
	{
		k1=y2-y1;
		k2=x2-x1;
		k=k1*10/k2;
		for(i=0;i<(x2-x1);i++)
			{
			  OLED_DrawPoint(x1+i,y1+i*k/10);
			}
	}
}
//x,y:圆心坐标
//r:圆的半径
void OLED_DrawCircle(uint8_t x,uint8_t y,uint8_t r)
{
	int a, b,num;
    a = 0;
    b = r;
    while(2 * b * b >= r * r)      
    {
        OLED_DrawPoint(x + a, y - b);
        OLED_DrawPoint(x - a, y - b);
        OLED_DrawPoint(x - a, y + b);
        OLED_DrawPoint(x + a, y + b);
 
        OLED_DrawPoint(x + b, y + a);
        OLED_DrawPoint(x + b, y - a);
        OLED_DrawPoint(x - b, y - a);
        OLED_DrawPoint(x - b, y + a);
        
        a++;
        num = (a * a + b * b) - r*r;//计算画的点离圆心的距离
        if(num > 0)
        {
            b--;
            a--;
        }
    }
}



//在指定位置显示一个字符,包括部分字符
//x:0~127
//y:0~63
//size:选择字体 12/16/24
void OLED_ShowChar(uint8_t x,uint8_t y,uint8_t chr,uint8_t size1)
{
	uint8_t i,m,temp,size2,chr1;
	uint8_t y0=y;
	size2=(size1/8+((size1%8)?1:0))*(size1/2);  //得到字体一个字符对应点阵集所占的字节数
	chr1=chr-' ';  //计算偏移后的值
	for(i=0;i<size2;i++)
	{
		if(size1==12)
        {temp=asc2_1206[chr1][i];} //调用1206字体
		else if(size1==16)
        {temp=asc2_1608[chr1][i];} //调用1608字体
		else if(size1==24)
        {temp=asc2_2412[chr1][i];} //调用2412字体
		else return;
				for(m=0;m<8;m++)           //写入数据
				{
					if(temp&0x80)OLED_DrawPoint(x,y);
					else OLED_ClearPoint(x,y);
					temp<<=1;
					y++;
					if((y-y0)==size1)
					{
						y=y0;
						x++;
						break;
          }
				}
  }
}


//显示字符串
//x,y:起点坐标  
//size1:字体大小 
//*chr:字符串起始地址 
void OLED_ShowString(uint8_t x,uint8_t y,uint8_t *chr,uint8_t size1)
{
	while((*chr>=' ')&&(*chr<='~'))//判断是不是非法字符!
	{
		OLED_ShowChar(x,y,*chr,size1);
		x+=size1/2;
		if(x>128-size1)  //换行
		{
			x=0;
			y+=2;
    }
		chr++;
  }
}

//m^n
uint32_t OLED_Pow(uint8_t m,uint8_t n)
{
	uint32_t result=1;
	while(n--)
	{
	  result*=m;
	}
	return result;
}

////显示2个数字
////x,y :起点坐标	 
////len :数字的位数
////size:字体大小
void OLED_ShowNum(uint8_t x,uint8_t y,uint32_t num,uint8_t len,uint8_t size1)
{
	uint8_t t,temp;
	for(t=0;t<len;t++)
	{
		temp=(num/OLED_Pow(10,len-t-1))%10;
			if(temp==0)
			{
				OLED_ShowChar(x+(size1/2)*t,y,'0',size1);
      }
			else 
			{
			  OLED_ShowChar(x+(size1/2)*t,y,temp+'0',size1);
			}
  }
}

//显示汉字
//x,y:起点坐标
//num:汉字对应的序号
void OLED_ShowChinese(uint8_t x,uint8_t y,uint8_t num,uint8_t size1)
{
	uint8_t i,m,n=0,temp,chr1;
	uint8_t x0=x,y0=y;
	uint8_t size3=size1/8;
	while(size3--)
	{
		chr1=num*size1/8+n;
		n++;
			for(i=0;i<size1;i++)
			{
				if(size1==16)
						{temp=Hzk1[chr1][i];}//调用16*16字体
				else if(size1==24)
						{}//temp=Hzk2[chr1][i];}//调用24*24字体
				else return;
							
						for(m=0;m<8;m++)
							{
								if(temp&0x01)OLED_DrawPoint(x,y);
								else OLED_ClearPoint(x,y);
								temp>>=1;
								y++;
							}
							x++;
							if((x-x0)==size1)
							{x=x0;y0=y0+8;}
							y=y0;
			 }
	}
}


//计算起始y像素不在SEG起始时所需偏移
// y 0~63
uint8_t OLED_WR_BP(uint8_t y,uint8_t Data,uint8_t Data2)
{
//	uint8_t temp[3]={/*设置列x*/\
//										0x00,/*0x00~0x0f*/\
//										0x10,/*0x10~0x1f*/\
//										/*设置行y--0xb0~0xb7*/\
//										0xb0};
	uint8_t y_temp=0;
	uint16_t tempbuf=(uint16_t)Data<<8|Data2;	
	y_temp=y%8;

	if(y_temp!=0)
	{
		
		return (uint8_t)(tempbuf>>(8-y_temp));
	}
	else
	{
		return Data;
	}									
}

//x0,y0：起点坐标
//x1,y1：终点坐标
//BMP[]：要写入的图片数组
void OLED_ShowPicture(uint8_t x0,uint8_t y0,uint8_t x1,uint16_t Len,const uint8_t *BMP)
{
	uint32_t j=0;
	uint8_t x=x0,y=y0/8;//y=5

	
	if((8-y)*(x1-x0)<Len)
	{
		Len=(8-y)*(x1-x0);
	}	
	while(j<Len)
	{

		if(x<x1)
		{
			if(j<(x1-x0))//检查第一段
			{
				OLED_GRAM[y][x]=OLED_WR_BP(y0,BMP[j],0);	
				j++;
				x++;			
			}
			else if(Len-j<=(x1-x0))//检查最后一段
			{
				OLED_GRAM[y][x]=OLED_WR_BP(y0,BMP[j],BMP[j-x1+x0]);
				if(y<7)
				{
					OLED_GRAM[y+1][x]=OLED_WR_BP(y0,0,BMP[j]);			
				}
				j++;
				x++;						
			}
			else
			{
				OLED_GRAM[y][x]=OLED_WR_BP(y0,BMP[j],BMP[j-x1+x0]);
				j++;
				x++;
			}
		}
		else
		{
			y++;
			x=x0;		
		}
	}
//	OLED_GRAM[y][x+1]=0xff;
}
//OLED的初始化
void OLED_Init(void)
{
  OLED_WR(InitD,28,OLED_CMD);
	OLED_WR(OriginD,3,OLED_CMD);
	OLED_ColorTurn(1);	
	OLED_DisplayTurn(1);
	OLED_Clear_Hard();
}

