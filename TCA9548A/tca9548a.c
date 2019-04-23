#include "stc8.h"
#include ".\STC8_IO_IIC\myiic.h"
#include "tca9548a.h"



void Open_Channel(uchar ch) //打开某个通道
{
	IIC_Stop();
	IIC_Start();
	IIC_WriteByte(TCS_addr | 0x00);
	check_Ack();

	IIC_WriteByte(ch);
	check_Ack();

	IIC_Stop();
}