#ifndef __TIMER4_H_
#define __TIMER4_H_

#define uint unsigned int
#define uchar unsigned char


void Timer4_Init();
void T4_delay(uchar z);//等待型
bit T4_delay_re(uchar z);//1定时完成，0还在定时中
	

#endif