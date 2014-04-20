/*
	encode: UTF-8
	object: 定时器T1 产生定时时钟  interrupt 3
					P1 控制8个发光二极管 8个指示灯依次一个一个闪动 频率 10次每秒循环
					8个灯依次亮一遍为一个周期
	info  : - T1 initial number
						每秒10次 每次走8个发光二极管 即每秒走10*8=80个二极管
						每个管用时 t= 1000ms / 80 = 12.5ms 定时 12.5ms
						机器周期 Tcy=12*(1/11059200)
						定时器初值 N= 12500/ Tcy = 11520
					- frequency
					

*/
#include <reg52.h>
#include <intrins.h>
#define uint unsigned int
#define uchar unsigned char

uchar code table[]={0xfe,0xfd,0xfb,0xf7,0xef,0xdf,0xbf,0x7f};
uchar num;

//void delayms (uchar ms)
//{
//	uint i,j;
//	for (i=ms; i>0; i--)
//		for (j=110; j>0; j--);
//}

void T1_timer() interrupt 3
{
	TH1=(65536-11520)/256;
	TL1=(65536-11520)%256;
	num++;
	if (num == 8)
		num=0;
}

void display (uchar num)
{
	P1=table[num];
	
}

void init ()
{
	TMOD=0x10;
	TH1=(65536-11520)/256;
	TL1=(65536-11520)%256;
	EA=1;
	ET1=1;
	TR1=1;
	num=0;
	
}

void main (void)
{
	init();
	while(1)
	{
		display(num);
	}
}
