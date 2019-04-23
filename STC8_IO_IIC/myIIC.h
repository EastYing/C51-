#ifndef __myiic_h_
#define __myiic_h_

#define uint unsigned int
#define uchar unsigned char
	
#define SDA  P43
#define SCL  P44




void IIC_delay(void);
void Init_MyIIC(void);//��ʼ��IIC
void IIC_Start(void);//IIC��ʼ�ź�
void IIC_Stop(void);//IICֹͣ�ź�
void IIC_Start(void);//IIC��ʼ�ź�
void Send_Ack(uchar a);//1Ӧ��,0��Ӧ��
void check_Ack(void);//�ȴ�Ӧ��	

uchar IIC_ReadByte(void);//��ȡһ���ֽ�
void IIC_WriteByte(uchar date);//д��һ���ֽ�

void IIC_test();


#endif
