#include "tcs3414.h"
#include ".\STC8_IO_IIC\myiic.h"



uchar Read_ID(void)//��ȡ����ID
{
	uchar temp;
	IIC_Start();
	IIC_WriteByte(TCSWRITE);//��ַ+д����
	check_Ack();//��Ӧ��

	IIC_WriteByte(BYTE_READ | ID);
	check_Ack();//��Ӧ��

	IIC_Start();//Start Again
	IIC_WriteByte(TCSREAD);	  //д��ַѡ�������
	check_Ack();//��Ӧ��

	temp=IIC_ReadByte();
	Send_Ack(0);//���ͷ�Ӧ��
	IIC_Stop();
	return temp;
}

uint Red_Color(void)//��ȡ��ɫ
{
	uint val = 0;
	uchar temp[2];
	IIC_Stop();

	IIC_Start();
	IIC_WriteByte(TCSWRITE);//ѡ��д����
	check_Ack();//��Ӧ��

	IIC_WriteByte(WORD_READ | RLOW);//���ֹ��ܣ���ɫ�Ĵ�����λ
	check_Ack();//��Ӧ��

	IIC_Start();
	IIC_WriteByte(TCSREAD);//ѡ�������
	check_Ack();//��Ӧ��
	temp[0]=IIC_ReadByte();//�ȶ�����8λ
	Send_Ack(1);//Ӧ��
	temp[1]=IIC_ReadByte();

	IIC_Stop();
	val=(temp[1]<<8) | temp[0];//��λ��λ��ϳ�16bit����
	return val;
}

uint Blue_Color(void)// ��ȡ��ɫ
{
	uint val;
	uchar temp[2];
	IIC_Stop();

	IIC_Start();
	IIC_WriteByte(TCSWRITE);
	check_Ack();//��Ӧ��

	IIC_WriteByte(WORD_READ | BLOW);
	check_Ack();//��Ӧ��

	IIC_Start();
	IIC_WriteByte(TCSREAD);
	check_Ack();//��Ӧ��

	temp[0]=IIC_ReadByte();
	Send_Ack(1);//Ӧ��
	temp[1]=IIC_ReadByte();
	IIC_Stop();
	val=(temp[1]<<8) | temp[0];
	return val;
}

uint Green_Color(void)//��ȡ��ɫ
{
	uint val;
	uchar temp[2];
	IIC_Stop();

	IIC_Start();
	IIC_WriteByte(TCSWRITE);
	check_Ack();//��Ӧ��

	IIC_WriteByte(WORD_READ | GLOW);
	check_Ack();//��Ӧ��

	IIC_Start();
	IIC_WriteByte(TCSREAD);
	check_Ack();//��Ӧ��

	temp[0]=IIC_ReadByte();
	Send_Ack(1);//Ӧ��
	temp[1]=IIC_ReadByte();
	IIC_Stop();
	val=(temp[1]<<8) | temp[0];
	return val;
}

uint Clear_Color(void)//��ȡ����ͨ��
{
	uint val;
	uchar temp[2];
	IIC_Stop();

	IIC_Start();
	IIC_WriteByte(TCSWRITE);
	check_Ack();//��Ӧ��

	IIC_WriteByte(WORD_READ | CLRLOW);
	check_Ack();//��Ӧ��

	IIC_Start();
	IIC_WriteByte(TCSREAD);
	check_Ack();//��Ӧ��

	temp[0]=IIC_ReadByte();
	Send_Ack(1);//Ӧ��
	temp[1]=IIC_ReadByte();
	IIC_Stop();
	val=(temp[1]<<8) | temp[0];
	return val;
}

void TCS3414_Init(void)//��ʼ��TCS3414
{
	Tcs3414_Set_TimingReg(INTEG_MODE_FREE);//��������ģʽ ffreeģʽ12ms
//	Tcs3414_Set_InterruptSource(INT_SOURCE_RED);//�����ж�Դ ����ɫ�ж�
//	Tcs3414_Set_InterruptConfig(INTR_DISABLE);//�����ж�ģʽ,�ر��ж�
	Tcs3414_Set_Gain(GAIN_1|PRESCALER_1);//�Ŵ�����Ԥ��Ƶ�� �˴����Ŵ󣬲���Ƶ
	Tcs3414_Set_EnableADC();//����ADCת��
}

void Tcs3414_Write_reg(uchar addr, uchar buff)  //дTCS�Ĵ���
{
	IIC_Start();
	IIC_WriteByte(0x39<<1 | 0x00);
	check_Ack();

	IIC_WriteByte(BYTE_READ | addr); //CMD + addr,�ֽ�д��ģʽ�ͼĴ�����ַ
	check_Ack();

	IIC_WriteByte(buff); //д������
	check_Ack();

	IIC_Stop();
}

/********************************************************************
*name:			Tcs3414_Set_TimingReg
*description:	���ô���ģʽ
*param: 		u8
*return: void
********************************************************************/
void Tcs3414_Set_TimingReg(uchar buff)
{
	Tcs3414_Write_reg(TIMING, buff);
}

/********************************************************************
*name:			Tcs3414_Set_InterruptSource
*description:	�����ж�Դ
*param: void
*return: void
********************************************************************/
void Tcs3414_Set_InterruptSource(uchar buff)
{
	Tcs3414_Write_reg(INTSOURCE, buff);
}

/********************************************************************
*name:			Tcs3414_Set_InterruptConfig
*description:	�����ж�Դģʽ
*param: void
*return: void
********************************************************************/
void Tcs3414_Set_InterruptConfig(uchar buff)	
{
	Tcs3414_Write_reg(INTERRUPT, buff);
}
/********************************************************************
*name:			Tcs3414_Set_Gain
*description:	���������źŷŴ���
*param: void
*return: void
********************************************************************/
void Tcs3414_Set_Gain(uchar buff)
{
	Tcs3414_Write_reg(GAIN, buff);
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
*name:			Tcs3414_Read_word
*description:	��ȡָ���ļĴ�����һ��word
*param: 		u8 addr �Ĵ�����ַ
*return: u16 
********************************************************************/
uint Tcs3414_Read_word(uchar addr)
{
	uint temp = 0;
	IIC_Start();				//�����ֲ� P12 Figure.19 ��ȡword ����
	IIC_WriteByte(0x39<<1 | 0x00);
	check_Ack();//��Ӧ��

	IIC_WriteByte(WORD_READ | addr);
	check_Ack();//��Ӧ��

	IIC_Start();
	IIC_WriteByte(0x39<<1 | 0x01);
	check_Ack();//��Ӧ��

	temp = IIC_ReadByte();
	Send_Ack(1);//Ӧ��
	temp = (IIC_ReadByte()<<8) | temp;
	IIC_Stop();
	return temp;
}
/********************************************************************
*����:			RGB���ݸ�������װ����8Bit��RGB��ֵ
*param: 		int R,G,B��ֵ��int Clear������ֵ
*return: 		ת�����8Bit��R,G,Bֵ 
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