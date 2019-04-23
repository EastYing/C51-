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


void Init_MyIIC(void)//��ʼ��IIC
{
	SDA = 1;
	IIC_delay();
	SCL = 1;
	IIC_delay();
}


void IIC_Start(void)//IIC��ʼ�ź�
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

void IIC_Stop(void)//IICֹͣ�ź�
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

void Send_Ack(uchar a)//����Ӧ��
{
	SCL = 0;
	IIC_delay();
	if(a == 1)	SDA = 0;// L ,����Ӧ��
	if(a == 0)	SDA = 1;// H ,���ͷ�Ӧ��
	IIC_delay();
	SCL = 1;
	IIC_delay();
	SCL = 0;
	IIC_delay();	
}


void check_Ack(void)//�ȴ�Ӧ��
{
	uchar j = 0;
	SCL = 1;
	IIC_delay();
	while((SDA == 1) && (j<255))//�����ȴ�ʱ��ӻ�δӦ����Ĭ�ϱ�ʾ�ӻ��Ѿ���������δӦ��
	{
		j ++ ;
	}
	
	SCL = 0;
	IIC_delay();
}



uchar IIC_ReadByte(void)//��ȡһ���ֽ�
{
	uchar i;
	uchar x = 0;
	SCL = 0;
	IIC_delay();
	SDA = 1;//�ͷ����ߣ�׼����������
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

void IIC_WriteByte(uchar date)//д��һ���ֽ�
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
	SDA=1;//�ͷ�����,׼������Ӧ���ź�
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

