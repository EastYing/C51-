#include "tcs3414.h"
#include "myiic.h"
#include "delay.h"
//struct SimuI2cPortType tcs3414_device;	//��ɫ�������豸
/********************************************************************
*name:			Tcs3414_i2c_Init
*description:	��ʼ��Tcs3414_Init�豸
*param: void
*return: void
********************************************************************/
void Tcs3414_i2c_Init(void)
{
	IIC_Init();			//��ʼ��IIC�ӿ�
}
/********************************************************************
*name:			Tcs3414_ReadOneByte
*description:	��ȡһ���ֽ�����
*param: 		void
*return: 		u8  ��ȡ��IIC�豸������
********************************************************************/
u8 Tcs3414_ReadOneByte(void) 
{	
	u8 temp = 0;	
	IIC_Start();	//�����ֲ� P11 Figure.15 ��ȡһ�ֽ�����
	IIC_Send_Byte(0x39<<1 | 0x01);	//0x39 I2C�豸��ַ + ��дλ 1 ��  0 д
	IIC_Wait_Ack();
	temp = IIC_Read_Byte(1);	//���� 1 ��IIC���豸����ackӦ�� 0 ��IIC���豸����nackӦ��
	IIC_Stop();
	return temp;
}
/********************************************************************
*name:			Tcs3414_WriteOneByte
*description:	д��һ���ֽ�����
*param: 		u8 reg ��д������
*return: 		void
********************************************************************/
void Tcs3414_WriteOneByte(u8 reg)
{
	IIC_Start();		//�����ֲ� P11 Figure.14 д��һ�ֽ�����
	IIC_Send_Byte(0x39<<1 | 0x00);//0x39 I2C�豸��ַ + ��дλ 1 ��  0 д
	IIC_Wait_Ack();
	IIC_Send_Byte(reg);
	IIC_Wait_Ack();
	IIC_Stop();
}
/********************************************************************
*name:			Tcs3414_Write_reg
*description:	������д��ָ���ļĴ���
*param: 		u8 addr �Ĵ�����ַ
				u8 reg  �Ĵ���ֵ
*return: void
********************************************************************/
void Tcs3414_Write_reg(u8 addr, u8 reg)
{
	IIC_Start();  //�����ֲ� P11 Figure.16 д��Byte ����
	IIC_Send_Byte(0x39<<1 | 0x00);
	IIC_Wait_Ack();
	IIC_Send_Byte(BYTE_READ |addr);//CMD + addr,д��ģʽ�ͼĴ�����ַ
	IIC_Wait_Ack();
	IIC_Send_Byte(reg);
	IIC_Wait_Ack();
	IIC_Stop();

}
/********************************************************************
*name:			Tcs3414_Read_reg
*description:	��ȡָ���ļĴ���
*param: 		u8 addr �Ĵ�����ַ
				u8 reg  �Ĵ���ֵ
*return: void
********************************************************************/
u8 Tcs3414_Read_reg(u8 addr)
{
	u8 temp = 0;		
	IIC_Start();
	IIC_Send_Byte(0x39<<1 | 0x00);		//�����ֲ� P11 Figure.17 ��ȡByte ����
	IIC_Wait_Ack();
	IIC_Send_Byte(BYTE_READ | addr);//CMD + addr,д��ģʽ�ͼĴ�����ַ
	IIC_Wait_Ack();
	IIC_Start();
	IIC_Send_Byte(0x39<<1 | 0x01);//д���վ��ַ��ѡ�������
	IIC_Wait_Ack();
	temp = IIC_Read_Byte(1);
	IIC_Stop();
	return temp;
}
/********************************************************************
*name:			Tcs3414_Read_word
*description:	��ȡָ���ļĴ�����һ��word
*param: 		u8 addr �Ĵ�����ַ
*return: u16 
********************************************************************/
u16 Tcs3414_Read_word(u8 addr)
{
	u16 temp = 0;
	IIC_Start();				//�����ֲ� P12 Figure.19 ��ȡword ����
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
*description:	��ʼ��Tcs3414_Init�豸
*param: void
*return: 		u8 ��ʼ����� 0 �ɹ� 1 ʧ��
********************************************************************/
u8 Tcs3414_Init(void) 
{
	u8 id = 0;
	Tcs3414_i2c_Init();
	id = Tcs3414_Read_ID();
	if((id&0xF0) != 0x10)	//�����ֲ�P18 Table.8 [7:4]= 0001 = 0x10 �豸ΪTCS3414...
	{
		return 1;
	}
	Tcs3414_Set_TimingReg(INTEG_MODE_FREE);//��������ģʽ ffreeģʽ12ms
	Tcs3414_Set_InterruptSource(INT_SOURCE_RED);//�����ж�Դ 
	Tcs3414_Set_InterruptConfig(INTR_LEVEL|INTR_PERSIST_EVERY);//�����ж�ģʽ
	Tcs3414_Set_Gain(GAIN_1|PRESCALER_4);//�Ŵ�����Ԥ��Ƶ�� �˴����Ŵ�
	Tcs3414_Set_EnableADC();//����ADCת��
	return 0;
}
/********************************************************************
*name:			Tcs3414_Set_TimingReg
*description:	���ô���ģʽ
*param: 		u8
*return: void
********************************************************************/
void Tcs3414_Set_TimingReg(u8 data)
{
	Tcs3414_Write_reg(TIMING, data);
}
/********************************************************************
*name:			Tcs3414_Set_InterruptSource
*description:	�����ж�Դ
*param: void
*return: void
********************************************************************/
void Tcs3414_Set_InterruptSource(u8 data)
{
	Tcs3414_Write_reg(INTSOURCE, data);
}
/********************************************************************
*name:			Tcs3414_Set_InterruptConfig
*description:	�����ж�Դģʽ
*param: void
*return: void
********************************************************************/
void Tcs3414_Set_InterruptConfig(u8 data)	
{
	Tcs3414_Write_reg(INTERRUPT, data);
}
/********************************************************************
*name:			Tcs3414_Set_Gain
*description:	���������źŷŴ���
*param: void
*return: void
********************************************************************/
void Tcs3414_Set_Gain(u8 data)
{
	Tcs3414_Write_reg(GAIN, data);
}
/********************************************************************
*name:			Tcs3414_Set_EnableADC
*description:	����ADCת��
*param: void
*return: void
********************************************************************/
void Tcs3414_Set_EnableADC(void)
{
	Tcs3414_Write_reg(CONTROL, CONTROL_VAL);
}

/********************************************************************
*name:			Tcs3414_Read_RGB
*description:	��ȡRGB
*param: void
*return: void
********************************************************************/
void Tcs3414_Read_RGB(u16 *r_data, u16 *g_data, u16 *b_data)
{
	*r_data = Tcs3414_Read_word(RLOW);		//����Rת������Ĵ����͵�ַ
	*g_data = Tcs3414_Read_word(GLOW);		//����Gת������Ĵ����͵�ַ
	*b_data = Tcs3414_Read_word(BLOW);		//����Bת������Ĵ����͵�ַ
}

/********************************************************************
*name:			Tcs3414_Read_ID
*description:	��ȡID
*param: 		u8 addr �Ĵ�����ַ
				u8 reg  �Ĵ���ֵ
*return: void
********************************************************************/
u8 Tcs3414_Read_ID(void)
{
	return(Tcs3414_Read_reg(ID));
}