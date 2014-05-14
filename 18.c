/*
	EXTERNAL INTERRUPT CONTROLING 7-SEGMENT DISPLAY
	**CAN NOT TEST**
  Author: wongsyrone
	Object: 
	Info: 
	INTR' -- INT0  L -- finish AD convert
	
*/

#include <reg52.h>
#include <intrins.h>

#define uint unsigned int
#define uchar unsigned char

sbit dula=P2^6;
sbit wela=P2^7;
sbit adwr=P3^6;
sbit adrd=P3^7;

uchar code table[]={
0x3f, 0x06, 0x5b, 0x4f,
0x66, 0x6d, 0x7d, 0x07,
0x7f, 0x6f, 0x77, 0x7c,
0x39, 0x5e, 0x79, 0x71};

void delay (uint xms)
{
	uint i,j;
	for (i=xms; i>0; i--)
		for (j=110; j>0; j--);
}

void display(uchar bai,uchar shi,uchar ge)
{
	dula=1;
	P0=table[bai];
	dula=0;
	P0=0xff;
	wela=1;
	P0=0x7e;
	wela=0;
	delay(5);
	
	dula=1;
	P0=table[shi];
	dula=0;
	P0=0xff;
	wela=1;
	P0=0x7d;
	wela=0;
	delay(5);
	
	dula=1;
	P0=table[ge];
	dula=0;
	P0=0xff;
	wela=1;
	P0=0x7b;
	wela=0;
	delay(5);
	
}

void INT_0() interrupt 0
{
	P1=0xff;
	adrd=1;
	_nop_();
	adrd=0;
	_nop_();
	adval=P1;
	adrd=1;
}

void main (void)
{
	
	uchar A1,A2,A3;
	uchar adval=0;
	wela=1;
	P0=0x7f;  // CS'
	wela=0;
	
	EA=1;
	EX0=1;
	
	while(1)
	{
		adwr=1;
		_nop_();
		adwr=0;
		_nop_();
		adwr=1;

		A1=adval/100;
		A2=adval%100/10;
		A3=adval%10;
		display(A1,A2,A3);

	}
}
