#ifndef TCS3414_H_
#define TCS3414_H_

#define uint unsigned int
#define uchar unsigned char

/**************TCS3414��ַ����******************/
//TCS3414�ĵ�ַλ0X72
#define TCSREAD 0x73 				// 0x72 | 0X01	IIC��ȡ����
#define TCSWRITE 0x72				//д����

#define CONTROL_VAL 0x03//��ADC�򿪵�Դ
#define INTEG_MODE_FREE 0x00	//��������������





//ADDRESS PART1
#define CONTROL 0x00
#define TIMING 0x01
#define INTERRUPT 0x02
#define INTSOURCE 0x03 //�ж�Դ�Ĵ���
#define ID 0x04
#define GAIN 0x07 //�Ŵ����Ĵ���
#define COLOR_BLOCK_READ 0x0F
#define GLOW 0x10		//G ��
#define GHIGH 0x11	//G ��
#define RLOW 0x12		//R ��
#define RHIGH 0x13	//R ��
#define BLOW 0x14		//B ��
#define BHIGH 0x15	//B ��
#define CLRLOW 0x16
#define CLRHIGH 0x17

//ADDRESS PART2
#define BLOCK_READ 0xC0
#define BYTE_READ 0x80		//�ֽڲ���
#define WORD_READ 0xA0		//�ֲ���
#define INT_CLR 0xE0



uchar Read_ID(void);//��ȡ����ID
uint Red_Color(void);//��ȡ��ɫ
uint Blue_Color(void);// ��ȡ��ɫ
uint Green_Color(void);//��ȡ��ɫ


//�ж�Դ�Ĵ���	0x03
#define INT_SOURCE_GREEN 0x00
#define INT_SOURCE_RED 0x01
#define INT_SOURCE_BLUE 0x10
#define INT_SOURCE_CLEAR 0x03
//�жϿ��ƼĴ��� 0x02
#define INTR_STOP 40
#define INTR_DISABLE 0x00
#define INTR_LEVEL 0x10
#define INTR_PERSIST_EVERY 0x00
#define INTR_PERSIST_SINGLE 0x01

//�Ŵ����Ĵ������� 0x07
#define GAIN_1 0x00	 //����
#define GAIN_4 0x10
#define GAIN_16 0x20
#define GANI_64 0x30

#define PRESCALER_1 0x00 //��Ƶ
#define PRESCALER_2 0x01
#define PRESCALER_4 0x02
#define PRESCALER_8 0x03
#define PRESCALER_16 0x04
#define PRESCALER_32 0x05
#define PRESCALER_64 0x06




uchar Read_ID(void);//��ȡ����ID
uint Red_Color(void);//��ȡ��ɫ
uint Blue_Color(void);// ��ȡ��ɫ
uint Green_Color(void);//��ȡ��ɫ
uint Clear_Color(void);//��ȡ����ͨ��
void TCS3414_Init(void);//��ʼ��TCS3414

void Tcs3414_Write_reg(uchar addr, uchar buff);  //дTCS�Ĵ���
void Tcs3414_Set_TimingReg(uchar buff);//���ô���ģʽ
void Tcs3414_Set_InterruptSource(uchar buff);//�����ж�Դ
void Tcs3414_Set_InterruptConfig(uchar buff);//�����ж�Դģʽ
void Tcs3414_Set_Gain(uchar buff);//���������źŷŴ���
void Tcs3414_Set_EnableADC(void);  //����ADCת��
uint Tcs3414_Read_word(uchar addr);//��ȡָ���ļĴ�����һ��word
uchar Count_RGB(uint color , uint Clear);//RGB���ݸ�������װ����8Bit��RGB��ֵ


#endif









