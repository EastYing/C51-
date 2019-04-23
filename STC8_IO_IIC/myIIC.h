#ifndef __myiic_h_
#define __myiic_h_

#define uint unsigned int
#define uchar unsigned char
	
#define SDA  P43
#define SCL  P44




void IIC_delay(void);
void Init_MyIIC(void);//初始化IIC
void IIC_Start(void);//IIC开始信号
void IIC_Stop(void);//IIC停止信号
void IIC_Start(void);//IIC开始信号
void Send_Ack(uchar a);//1应答,0非应答
void check_Ack(void);//等待应答	

uchar IIC_ReadByte(void);//读取一个字节
void IIC_WriteByte(uchar date);//写入一个字节

void IIC_test();


#endif
