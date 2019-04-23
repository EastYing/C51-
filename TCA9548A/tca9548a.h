#ifndef __tca9548a_h_
#define __tca9548a_h_

#define TCS_addr 0xe0//地址

#define uint unsigned int
#define uchar unsigned char

#define Ch0_open	0x01
#define Ch0_close	0x00

#define Ch1_open	0x02
#define Ch1_close	0x00

#define Ch2_open	0x04
#define Ch2_close	0x00

#define Ch3_open	0x08
#define Ch3_close	0x00

#define Ch4_open	0x10
#define Ch4_close	0x00

#define Ch5_open	0x20
#define Ch5_close	0x00

#define Ch6_open	0x40
#define Ch6_close	0x00

#define Ch7_open	0x80
#define Ch7_close	0x00

#define Open_all	0XFF
#define	Close_all	0x00

void Open_Channel(uchar ch);//打开某个通道

#endif
