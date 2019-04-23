#ifndef	__uart_h_
#define __uart_h_

#define uchar unsigned char
#define uint unsigned int


				   
//======================================================================================
//#define FOSC   24000000UL	 				//����2ʹ��
#define FOSC   11059200UL	 				//����2ʹ��
#define BRT    (65536 - FOSC / 9600 / 4)  //����2ʹ��,������ֱ���ڴ˸���
#define S2RI 0x01        //����2�����ж������־λ
#define S2TI 0x02        //����2�����ж������־λ

void Uart2_Init();
void Uart2_send_byte(uchar dat);	//����һ���ֽ�
void Uart2_send_str(uchar *s);   //�����ַ���



#endif