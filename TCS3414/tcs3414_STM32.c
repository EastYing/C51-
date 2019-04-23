#include "tcs3414.h"
#include "myiic.h"
#include "delay.h"
//struct SimuI2cPortType tcs3414_device;	//颜色传感器设备
/********************************************************************
*name:			Tcs3414_i2c_Init
*description:	初始化Tcs3414_Init设备
*param: void
*return: void
********************************************************************/
void Tcs3414_i2c_Init(void)
{
	IIC_Init();			//初始化IIC接口
}
/********************************************************************
*name:			Tcs3414_ReadOneByte
*description:	读取一个字节数据
*param: 		void
*return: 		u8  读取到IIC设备的数据
********************************************************************/
u8 Tcs3414_ReadOneByte(void) 
{	
	u8 temp = 0;	
	IIC_Start();	//数据手册 P11 Figure.15 读取一字节数据
	IIC_Send_Byte(0x39<<1 | 0x01);	//0x39 I2C设备地址 + 读写位 1 读  0 写
	IIC_Wait_Ack();
	temp = IIC_Read_Byte(1);	//参数 1 向IIC从设备返回ack应答 0 向IIC从设备返回nack应答
	IIC_Stop();
	return temp;
}
/********************************************************************
*name:			Tcs3414_WriteOneByte
*description:	写入一个字节数据
*param: 		u8 reg 待写入数据
*return: 		void
********************************************************************/
void Tcs3414_WriteOneByte(u8 reg)
{
	IIC_Start();		//数据手册 P11 Figure.14 写入一字节数据
	IIC_Send_Byte(0x39<<1 | 0x00);//0x39 I2C设备地址 + 读写位 1 读  0 写
	IIC_Wait_Ack();
	IIC_Send_Byte(reg);
	IIC_Wait_Ack();
	IIC_Stop();
}
/********************************************************************
*name:			Tcs3414_Write_reg
*description:	将数据写入指定的寄存器
*param: 		u8 addr 寄存器地址
				u8 reg  寄存器值
*return: void
********************************************************************/
void Tcs3414_Write_reg(u8 addr, u8 reg)
{
	IIC_Start();  //数据手册 P11 Figure.16 写入Byte 数据
	IIC_Send_Byte(0x39<<1 | 0x00);
	IIC_Wait_Ack();
	IIC_Send_Byte(BYTE_READ |addr);//CMD + addr,写入模式和寄存器地址
	IIC_Wait_Ack();
	IIC_Send_Byte(reg);
	IIC_Wait_Ack();
	IIC_Stop();

}
/********************************************************************
*name:			Tcs3414_Read_reg
*description:	读取指定的寄存器
*param: 		u8 addr 寄存器地址
				u8 reg  寄存器值
*return: void
********************************************************************/
u8 Tcs3414_Read_reg(u8 addr)
{
	u8 temp = 0;		
	IIC_Start();
	IIC_Send_Byte(0x39<<1 | 0x00);		//数据手册 P11 Figure.17 读取Byte 数据
	IIC_Wait_Ack();
	IIC_Send_Byte(BYTE_READ | addr);//CMD + addr,写入模式和寄存器地址
	IIC_Wait_Ack();
	IIC_Start();
	IIC_Send_Byte(0x39<<1 | 0x01);//写入从站地址，选择读功能
	IIC_Wait_Ack();
	temp = IIC_Read_Byte(1);
	IIC_Stop();
	return temp;
}
/********************************************************************
*name:			Tcs3414_Read_word
*description:	读取指定的寄存器的一个word
*param: 		u8 addr 寄存器地址
*return: u16 
********************************************************************/
u16 Tcs3414_Read_word(u8 addr)
{
	u16 temp = 0;
	IIC_Start();				//数据手册 P12 Figure.19 读取word 数据
	IIC_Send_Byte(0x39<<1 | 0x00);
	IIC_Wait_Ack();
	IIC_Send_Byte(WORD_READ | addr);
	IIC_Wait_Ack();
	IIC_Start();
	IIC_Send_Byte(0x39<<1 | 0x01);
	IIC_Wait_Ack();
	temp = IIC_Read_Byte(1);
	temp = (IIC_Read_Byte(1)<<8) | temp;
	IIC_Stop();
	return temp;
}
/********************************************************************
*name:			Tcs3414_Init
*description:	初始化Tcs3414_Init设备
*param: void
*return: 		u8 初始化结果 0 成功 1 失败
********************************************************************/
u8 Tcs3414_Init(void) 
{
	u8 id = 0;
	Tcs3414_i2c_Init();
	id = Tcs3414_Read_ID();
	if((id&0xF0) != 0x10)	//数据手册P18 Table.8 [7:4]= 0001 = 0x10 设备为TCS3414...
	{
		return 1;
	}
	Tcs3414_Set_TimingReg(INTEG_MODE_FREE);//设置运行模式 ffree模式12ms
	Tcs3414_Set_InterruptSource(INT_SOURCE_RED);//设置中断源 
	Tcs3414_Set_InterruptConfig(INTR_LEVEL|INTR_PERSIST_EVERY);//配置中断模式
	Tcs3414_Set_Gain(GAIN_1|PRESCALER_4);//放大倍数和预分频器 此处不放大
	Tcs3414_Set_EnableADC();//启动ADC转换
	return 0;
}
/********************************************************************
*name:			Tcs3414_Set_TimingReg
*description:	设置触发模式
*param: 		u8
*return: void
********************************************************************/
void Tcs3414_Set_TimingReg(u8 data)
{
	Tcs3414_Write_reg(TIMING, data);
}
/********************************************************************
*name:			Tcs3414_Set_InterruptSource
*description:	设置中断源
*param: void
*return: void
********************************************************************/
void Tcs3414_Set_InterruptSource(u8 data)
{
	Tcs3414_Write_reg(INTSOURCE, data);
}
/********************************************************************
*name:			Tcs3414_Set_InterruptConfig
*description:	设置中断源模式
*param: void
*return: void
********************************************************************/
void Tcs3414_Set_InterruptConfig(u8 data)	
{
	Tcs3414_Write_reg(INTERRUPT, data);
}
/********************************************************************
*name:			Tcs3414_Set_Gain
*description:	设置输入信号放大倍数
*param: void
*return: void
********************************************************************/
void Tcs3414_Set_Gain(u8 data)
{
	Tcs3414_Write_reg(GAIN, data);
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
*name:			Tcs3414_Read_RGB
*description:	读取RGB
*param: void
*return: void
********************************************************************/
void Tcs3414_Read_RGB(u16 *r_data, u16 *g_data, u16 *b_data)
{
	*r_data = Tcs3414_Read_word(RLOW);		//传入R转换结果寄存器低地址
	*g_data = Tcs3414_Read_word(GLOW);		//传入G转换结果寄存器低地址
	*b_data = Tcs3414_Read_word(BLOW);		//传入B转换结果寄存器低地址
}

/********************************************************************
*name:			Tcs3414_Read_ID
*description:	读取ID
*param: 		u8 addr 寄存器地址
				u8 reg  寄存器值
*return: void
********************************************************************/
u8 Tcs3414_Read_ID(void)
{
	return(Tcs3414_Read_reg(ID));
}