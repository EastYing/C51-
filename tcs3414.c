#include "tcs3414.h"
#include ".\STC8_IO_IIC\myiic.h"



uchar Read_ID(void)//读取器件ID
{
	uchar temp;
	IIC_Start();
	IIC_WriteByte(TCSWRITE);//地址+写功能
	check_Ack();//等应答

	IIC_WriteByte(BYTE_READ | ID);
	check_Ack();//等应答

	IIC_Start();//Start Again
	IIC_WriteByte(TCSREAD);	  //写地址选择读功能
	check_Ack();//等应答

	temp=IIC_ReadByte();
	Send_Ack(0);//发送非应答
	IIC_Stop();
	return temp;
}

uint Red_Color(void)//读取红色
{
	uint val = 0;
	uchar temp[2];
	IIC_Stop();

	IIC_Start();
	IIC_WriteByte(TCSWRITE);//选择写功能
	check_Ack();//等应答

	IIC_WriteByte(WORD_READ | RLOW);//读字功能，红色寄存器地位
	check_Ack();//等应答

	IIC_Start();
	IIC_WriteByte(TCSREAD);//选择读功能
	check_Ack();//等应答
	temp[0]=IIC_ReadByte();//先读到底8位
	Send_Ack(1);//应答
	temp[1]=IIC_ReadByte();

	IIC_Stop();
	val=(temp[1]<<8) | temp[0];//高位移位组合成16bit数据
	return val;
}

uint Blue_Color(void)// 读取蓝色
{
	uint val;
	uchar temp[2];
	IIC_Stop();

	IIC_Start();
	IIC_WriteByte(TCSWRITE);
	check_Ack();//等应答

	IIC_WriteByte(WORD_READ | BLOW);
	check_Ack();//等应答

	IIC_Start();
	IIC_WriteByte(TCSREAD);
	check_Ack();//等应答

	temp[0]=IIC_ReadByte();
	Send_Ack(1);//应答
	temp[1]=IIC_ReadByte();
	IIC_Stop();
	val=(temp[1]<<8) | temp[0];
	return val;
}

uint Green_Color(void)//读取绿色
{
	uint val;
	uchar temp[2];
	IIC_Stop();

	IIC_Start();
	IIC_WriteByte(TCSWRITE);
	check_Ack();//等应答

	IIC_WriteByte(WORD_READ | GLOW);
	check_Ack();//等应答

	IIC_Start();
	IIC_WriteByte(TCSREAD);
	check_Ack();//等应答

	temp[0]=IIC_ReadByte();
	Send_Ack(1);//应答
	temp[1]=IIC_ReadByte();
	IIC_Stop();
	val=(temp[1]<<8) | temp[0];
	return val;
}

uint Clear_Color(void)//读取清晰通道
{
	uint val;
	uchar temp[2];
	IIC_Stop();

	IIC_Start();
	IIC_WriteByte(TCSWRITE);
	check_Ack();//等应答

	IIC_WriteByte(WORD_READ | CLRLOW);
	check_Ack();//等应答

	IIC_Start();
	IIC_WriteByte(TCSREAD);
	check_Ack();//等应答

	temp[0]=IIC_ReadByte();
	Send_Ack(1);//应答
	temp[1]=IIC_ReadByte();
	IIC_Stop();
	val=(temp[1]<<8) | temp[0];
	return val;
}

void TCS3414_Init(void)//初始化TCS3414
{
	Tcs3414_Set_TimingReg(INTEG_MODE_FREE);//设置运行模式 ffree模式12ms
//	Tcs3414_Set_InterruptSource(INT_SOURCE_RED);//设置中断源 ，红色中断
//	Tcs3414_Set_InterruptConfig(INTR_DISABLE);//配置中断模式,关闭中断
	Tcs3414_Set_Gain(GAIN_1|PRESCALER_1);//放大倍数和预分频器 此处不放大，不分频
	Tcs3414_Set_EnableADC();//启动ADC转换
}

void Tcs3414_Write_reg(uchar addr, uchar buff)  //写TCS寄存器
{
	IIC_Start();
	IIC_WriteByte(0x39<<1 | 0x00);
	check_Ack();

	IIC_WriteByte(BYTE_READ | addr); //CMD + addr,字节写入模式和寄存器地址
	check_Ack();

	IIC_WriteByte(buff); //写入数据
	check_Ack();

	IIC_Stop();
}

/********************************************************************
*name:			Tcs3414_Set_TimingReg
*description:	设置触发模式
*param: 		u8
*return: void
********************************************************************/
void Tcs3414_Set_TimingReg(uchar buff)
{
	Tcs3414_Write_reg(TIMING, buff);
}

/********************************************************************
*name:			Tcs3414_Set_InterruptSource
*description:	设置中断源
*param: void
*return: void
********************************************************************/
void Tcs3414_Set_InterruptSource(uchar buff)
{
	Tcs3414_Write_reg(INTSOURCE, buff);
}

/********************************************************************
*name:			Tcs3414_Set_InterruptConfig
*description:	设置中断源模式
*param: void
*return: void
********************************************************************/
void Tcs3414_Set_InterruptConfig(uchar buff)	
{
	Tcs3414_Write_reg(INTERRUPT, buff);
}
/********************************************************************
*name:			Tcs3414_Set_Gain
*description:	设置输入信号放大倍数
*param: void
*return: void
********************************************************************/
void Tcs3414_Set_Gain(uchar buff)
{
	Tcs3414_Write_reg(GAIN, buff);
}

/********************************************************************
*name:			Tcs3414_Set_EnableADC
*description:	启动ADC转换
*param: void
*return: void
********************************************************************/
void Tcs3414_Set_EnableADC(void)
{
	Tcs3414_Write_reg(CONTROL, CONTROL_VAL);
}

/********************************************************************
*name:			Tcs3414_Read_word
*description:	读取指定的寄存器的一个word
*param: 		u8 addr 寄存器地址
*return: u16 
********************************************************************/
uint Tcs3414_Read_word(uchar addr)
{
	uint temp = 0;
	IIC_Start();				//数据手册 P12 Figure.19 读取word 数据
	IIC_WriteByte(0x39<<1 | 0x00);
	check_Ack();//等应答

	IIC_WriteByte(WORD_READ | addr);
	check_Ack();//等应答

	IIC_Start();
	IIC_WriteByte(0x39<<1 | 0x01);
	check_Ack();//等应答

	temp = IIC_ReadByte();
	Send_Ack(1);//应答
	temp = (IIC_ReadByte()<<8) | temp;
	IIC_Stop();
	return temp;
}
/********************************************************************
*功能:			RGB数据根据亮度装换成8Bit的RGB数值
*param: 		int R,G,B的值，int Clear清晰度值
*return: 		转换后的8Bit的R,G,B值 
********************************************************************/
uchar Count_RGB(uint color , uint Clear)
{
	uchar num;
	if( Clear > 1)
	{
		num = color / (Clear/255.0);	
		return	num;	
	}
	else	return 0;			
}