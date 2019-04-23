#include "stc8.h"
#include ".\Timer4\Timer4.h"

uchar T4_buff ;

void Timer4_Init()////10毫秒@11.0592MHz
{
	T4T3M &= 0xDF;		//定时器时钟12T模式
	T4L = 0x00;				//设置定时初值
	T4H = 0xdc;				//设置定时初值
	
	IE2 |= 0x40;   		//使能定时器中断
	T4T3M |= T4R; 		//启动定时器 0X80
//	EA = 1;
}



/***********************************
**@说明:T4定时器精准延时，等待
**@输入参数: 单位10MS
**@返回值: 
***********************************/	
void T4_delay(uchar z)
{
		T4_buff = z;
				
		while(T4_buff);
}

/***********************************
**@说明:T4定时器精准延时，返回型
**@输入参数: 单位10MS
**@返回值: 1定时完成，0还在定时中
***********************************/	
bit T4_delay_re(uchar z)
{
		T4_buff = z;
		
		if(T4_buff <= 20)
		{
			return 1;//定时完成
		}
		
		return 0;
}






void TM4_Isr() interrupt 20 using 1//10ms中断一次
{
	T4_buff --;
	
//	if(P02 == 0)
//	{
//		if(P02 == 0)	Key_buff ='r';
//	}
	
  AUXINTIF &= ~T4IF;                          //清中断标志
}







