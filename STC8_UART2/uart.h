#ifndef	__uart_h_
#define __uart_h_

#define uchar unsigned char
#define uint unsigned int


				   
//======================================================================================
//#define FOSC   24000000UL	 				//串口2使用
#define FOSC   11059200UL	 				//串口2使用
#define BRT    (65536 - FOSC / 9600 / 4)  //串口2使用,波特率直接在此更改
#define S2RI 0x01        //串口2接收中断请求标志位
#define S2TI 0x02        //串口2发送中断请求标志位

void Uart2_Init();
void Uart2_send_byte(uchar dat);	//发送一个字节
void Uart2_send_str(uchar *s);   //发送字符串



#endif