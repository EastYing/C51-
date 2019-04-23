#include "myiic.h"
#include "stc8.h"
#include "stdio.h"
#include "intrins.h"//	_nop_();


void IIC_delay(void)
{
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
}


void Init_MyIIC(void)//初始化IIC
{
	SDA = 1;
	IIC_delay();
	SCL = 1;
	IIC_delay();
}


void IIC_Start(void)//IIC开始信号
{
	SDA=1;
	IIC_delay();
	SCL=1;
	IIC_delay();
	SDA=0;
	IIC_delay();
	SCL = 0;
	IIC_delay();
}

void IIC_Stop(void)//IIC停止信号
{
	SDA=0;
	IIC_delay();
	SCL=1;
	IIC_delay();
	SDA=1;
	IIC_delay();
//	SCL = 0;
//	IIC_delay();
}

void Send_Ack(uchar a)//发送应答
{
	SCL = 0;
	IIC_delay();
	if(a == 1)	SDA = 0;// L ,发送应答
	if(a == 0)	SDA = 1;// H ,发送非应答
	IIC_delay();
	SCL = 1;
	IIC_delay();
	SCL = 0;
	IIC_delay();	
}


void check_Ack(void)//等待应答
{
	uchar j = 0;
	SCL = 1;
	IIC_delay();
	while((SDA == 1) && (j<255))//超出等待时间从机未应答，则默认表示从机已经收完数据未应答
	{
		j ++ ;
	}
	
	SCL = 0;
	IIC_delay();
}



uchar IIC_ReadByte(void)//读取一个字节
{
	uchar i;
	uchar x = 0;
	SCL = 0;
	IIC_delay();
	SDA = 1;//释放总线，准备接收数据
	IIC_delay();
	for(i=0;i<8;i++)
	{
		SCL = 1;
		IIC_delay();
		x <<= 1;
		x |= (uchar)SDA;
		SCL = 0;
		IIC_delay();
	}
	return x;
}

void IIC_WriteByte(uchar date)//写入一个字节
{
	uchar i;
	
	for(i=0;i<8;i++)
	{
		if((date<<i) & 0x80)	SDA = 1;
		else SDA = 0;
		IIC_delay();
		SCL = 1;
		IIC_delay();
		SCL = 0;
	}
	SCL=0;
	IIC_delay();
	SDA=1;//释放总线,准备接收应答信号
	IIC_delay();
}



void IIC_test()
{
	SDA = 0;
	SCL = 0;

	SDA = 1;
	SCL = 1;
	
	SDA = 0;
	SCL = 0;
	
	SDA = 1;
	SCL = 1;
}

