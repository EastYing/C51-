#include "stc8.h"
#include "uart.h"
#include "stdlib.h"	//�ַ���������
#include "stdio.h"
#include "string.h"


/*******************************************************************************
**���ܣ�		����2��ʼ������,9600-8-N-1��ʹ�ö�ʱ��2
**���������	��
**���������	��
**����ֵ��		��
*******************************************************************************/
void Uart2_Init()
{
	S2CON = 0x10;//ģʽ0��10λ�첽�շ����򿪴���2ʹ��
	T2L = BRT;
	T2H = BRT >> 8;
	AUXR = 0x14;//��ʱ��2ʱ��ΪFosc,��1T
	
//	AUXR &= 0xFB;		//��ʱ��2ʱ��ΪFosc/12,��12T
	
	IE2 |= 0x01;	 //��������2 �ж�

	
	//P_SW2 = 0X01;//RXD2_2 P40,TXD2_2 P42

	EA=1;	  //�����ж�
}



/*******************************************************************************
**���ܣ�		ʹ�ô���2����һ���ֽ�

**���������	dat Ҫ���͵��ֽ�
**���������	��
**����ֵ��		��
*******************************************************************************/
void Uart2_send_byte(uchar dat)	//����һ���ֽ�
{
	IE2 &= 0xfe;	 //�رմ���2 �ж�
	S2BUF = dat;
	while(!(S2CON & S2TI));  //��S2TI=0���ڴ˵ȴ�
    S2CON &= ~S2TI;          //����2�ķ��ͱ�־TI����
	IE2 |= 0x01;	 //�򿪴���2 �ж�
}
/*******************************************************************************
**���ܣ�		ʹ�ô���2�����ַ���

**���������	*S �ַ����׵�ַ
**���������	��
**����ֵ��		��
*******************************************************************************/
void Uart2_send_str(uchar *s)   //�����ַ���
{
	uint u = 0;

	while(*s)	//���ǿգ����ǿ��ֽڼ� 0
	{
		Uart2_send_byte(*s++);
//		s++;
		u++;
		if(u >256)	return;	//������ֽ����жϣ�������ֱ���˳�
	}
}



//void UART2_Isr() interrupt 8 //���ڶ��жϴ�������
//{
//    if (S2CON & 0x02)
//    {
//        S2CON &= ~0x02; //������жϱ�־
//    }

//    if(S2CON & 0x01) //�յ��ַ�������
//    {		
//       S2CON &= ~0x01; //�巢���жϱ�־
//    }	  
//}					  