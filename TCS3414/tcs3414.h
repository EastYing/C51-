#ifndef TCS3414_H_
#define TCS3414_H_

#define uint unsigned int
#define uchar unsigned char

/**************TCS3414地址定义******************/
//TCS3414的地址位0X72
#define TCSREAD 0x73 				// 0x72 | 0X01	IIC读取功能
#define TCSWRITE 0x72				//写功能

#define CONTROL_VAL 0x03//打开ADC打开电源
#define INTEG_MODE_FREE 0x00	//积分器自由运行





//ADDRESS PART1
#define CONTROL 0x00
#define TIMING 0x01
#define INTERRUPT 0x02
#define INTSOURCE 0x03 //中断源寄存器
#define ID 0x04
#define GAIN 0x07 //放大倍数寄存器
#define COLOR_BLOCK_READ 0x0F
#define GLOW 0x10		//G 低
#define GHIGH 0x11	//G 高
#define RLOW 0x12		//R 低
#define RHIGH 0x13	//R 低
#define BLOW 0x14		//B 低
#define BHIGH 0x15	//B 低
#define CLRLOW 0x16
#define CLRHIGH 0x17

//ADDRESS PART2
#define BLOCK_READ 0xC0
#define BYTE_READ 0x80		//字节操作
#define WORD_READ 0xA0		//字操作
#define INT_CLR 0xE0



uchar Read_ID(void);//读取器件ID
uint Red_Color(void);//读取红色
uint Blue_Color(void);// 读取蓝色
uint Green_Color(void);//读取绿色


//中断源寄存器	0x03
#define INT_SOURCE_GREEN 0x00
#define INT_SOURCE_RED 0x01
#define INT_SOURCE_BLUE 0x10
#define INT_SOURCE_CLEAR 0x03
//中断控制寄存器 0x02
#define INTR_STOP 40
#define INTR_DISABLE 0x00
#define INTR_LEVEL 0x10
#define INTR_PERSIST_EVERY 0x00
#define INTR_PERSIST_SINGLE 0x01

//放大倍数寄存器设置 0x07
#define GAIN_1 0x00	 //倍数
#define GAIN_4 0x10
#define GAIN_16 0x20
#define GANI_64 0x30

#define PRESCALER_1 0x00 //分频
#define PRESCALER_2 0x01
#define PRESCALER_4 0x02
#define PRESCALER_8 0x03
#define PRESCALER_16 0x04
#define PRESCALER_32 0x05
#define PRESCALER_64 0x06




uchar Read_ID(void);//读取器件ID
uint Red_Color(void);//读取红色
uint Blue_Color(void);// 读取蓝色
uint Green_Color(void);//读取绿色
uint Clear_Color(void);//读取清晰通道
void TCS3414_Init(void);//初始化TCS3414

void Tcs3414_Write_reg(uchar addr, uchar buff);  //写TCS寄存器
void Tcs3414_Set_TimingReg(uchar buff);//设置触发模式
void Tcs3414_Set_InterruptSource(uchar buff);//设置中断源
void Tcs3414_Set_InterruptConfig(uchar buff);//设置中断源模式
void Tcs3414_Set_Gain(uchar buff);//设置输入信号放大倍数
void Tcs3414_Set_EnableADC(void);  //启动ADC转换
uint Tcs3414_Read_word(uchar addr);//读取指定的寄存器的一个word
uchar Count_RGB(uint color , uint Clear);//RGB数据根据亮度装换成8Bit的RGB数值


#endif









