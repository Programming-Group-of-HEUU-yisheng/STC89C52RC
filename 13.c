/*
	object: ��ʱ��  �Լ��500 ms��6λ�������������ʾ0-F�ظ�  interrupt 1
		
	info:	 - T1 initial number  50ms  45872
		all six seven-segment display show the same thing
		��̬��ʾ
	TODO:	1. ȫ����ܶ�̬��ʾ�������������/�տ�ʼ��һλ0�����һλ5��Ȼ�����ε��������ڹ�������ʽ
*/
#include <reg52.h>
#define uint unsigned int
#define uchar unsigned char

sbit dula=P2^6;
sbit wela=P2^7;

uchar code table[]={
0x3f,0x06,0x5b,0x4f,
0x66,0x6d,0x7d,0x07,
0x7f,0x6f,0x77,0x7c,
0x39,0x5e,0x79,0x71};

uchar num,num1;

//void delayms (uchar ms)
//{
//	uint i,j;
//	for (i=ms; i>0; i--)
//		for (j=110; j>0; j--);
//}

void T0_timer() interrupt 1
{
	// 50ms * 10 = 500ms
	TH0=(65536-45872)/256;
	TL0=(65536-45872)%256;
	num++;
	if (num == 10)  // 500 ms reached
	{
		num=0;
		num1++;
		if (num1 == 16)
		{
			num1=0;
		}
	}
}

void display (uchar num)
{
	dula=1;
	P0=table[num];
	dula=0;
}

void init ()
{
	TMOD=0x01;
	TH0=(65536-45872)/256;
	TL0=(65536-45872)%256;
	EA=1;
	ET0=1;
	TR0=1;
	
	wela=1;
	P0=0xc0;
	wela=0;
	
	num=0;
	num1=0;
}

void main (void)
{
	init();
	while(1)
	{
		display(num1);
	}
}
