/*
	How to delay the display in the correct way
	Need to find a better way than setting a big number to delay,which way is not very good
	Maybe we can use the interrupt to make timer more accurate
	
	TODO:
	- Find a number to make timer happy  6*150=900
	- Use interrupt in 8051 MCU
*/


#include <reg52.h>

#define uint unsigned int
#define uchar unsigned char

sbit dula=P2^6;   //  what to show
sbit wela=P2^7;   //  which one to show

// The first screen: show "11-d-1"
uchar code screen1[]={
0x06,0x06,0x40,
0x5e,0x40,0x06};

// The second screen: show (201114) "050118"
uchar code screen2[]={
0x3f,0x6d,0x3f,
0x06,0x06,0x7f};

/* 
choose which we should display
from left to right
*/
uchar code choice[]={
0xfe,0xfd,0xfb,
0xf7,0xef,0xdf};

uint a,b;
uint i,j;

void delayms (uint xms)
{
	uint i,j;
	for (i=xms; i>0; i--)
		for (j=110; j>0; j--);
}

void main (void)
{
	while(1)
	{

		for (i=150; i>0; i--)  /* TODO: This number to be searched - 6*150=900*/
		{
			for (a=0; a<6; a++)
			{
			dula=1;
			P0=screen1[a];
			dula=0;
			P0=0xff;  // clean to avoid errors
			wela=1;
			P0=choice[a];
			wela=0;
			delayms(1);
			}
		}
		/* make our display empty */
		wela=1;
		P0=0xff;
		wela=0;
		delayms(1000);
		
	
		for (j=150; j>0; j--)     /* TODO: This is the same as above */
		{
			for (b=0; b<6; b++)
			{
			dula=1;
			P0=screen2[b];
			dula=0;
			P0=0xff;  // clean to avoid errors
			wela=1;
			P0=choice[b];
			wela=0;
			delayms(1);
			}
		}
		/* make our display empty */
		wela=1;
		P0=0xff;
		wela=0;
		delayms(1000);
	}
}