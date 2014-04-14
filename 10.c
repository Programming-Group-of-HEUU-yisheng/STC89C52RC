/*
	This is the INTERRUPT version, we using timer interrupt in the 8051 mcu
		to make it accurate when display something
	The interrupt part only have timer initialization, and put other statement
		into main() or sub-functions
	
	something we should know
	- EA...interrupt enable
	- ET0... Timer 0 
	
	TODO:
	- 

*/

#include <reg52.h>
#define uint unsigned int
#define uchar unsigned char

sbit dula=P2^6;   //  what to show
sbit wela=P2^7;   //  which one to show

/* 
initial flag, which means show something  
op_scr=1 ... display screen 1; op_scr=0 ... display screen 2
op_switch=1 ... show ; op_switch=0 ... clear
*/
bit op_scr=1;
bit op_switch=1;

/*
	define what we will display 
	screen1...11-d-1
	screen2...050118
	choice...from left to right, for dynamic display purpose only
*/
uchar code screen1[]={0x06,0x06,0x40,0x5e,0x40,0x06};
uchar code screen2[]={0x3f,0x6d,0x3f,0x06,0x06,0x7f};
uchar code choice[]={0xfe,0xfd,0xfb,0xf7,0xef,0xdf};

uchar num;

//void delayms (uint ms)
//{
//	uint i,j;
//	for (i=ms; i>0; i--)
//		for (j=110; j>0; j--);
//}

/*
        0     1000     2000   3000  | 4000
scr     1       1        0      0   |   1      
switch  1       0        1      0   |   1
num     0       20       40     60  |   80 
*/
void T0_timer() interrupt 1
{
	// 1 sec
	TH0=(65536-45872)/256;
	TL0=(65536-45872)%256;
	num++;
	if (num == 20 || num == 40 || num == 60)
	{
		op_switch=~op_switch;
		if (num == 40)
		{
			op_scr=~op_scr;
			if (num == 80)  // 4 sec
				num=0;
		}
	}
}

void show_screen1 (void)
{
	uchar a,j;
	while (op_scr == 1)
	{
	for (a=0; a<6; a++)
		{
			dula=1;
			P0=screen1[a];
			dula=0;
			P0=0xff;
			wela=1;
			P0=choice[a];
			wela=0;
			for (j=100; j>0; j--);
		}
	}

}

void show_screen2 (void)
{
	uchar b,j;
	while (op_scr == 0)
	{
	for (b=0; b<6; b++)
		{
			dula=1;
			P0=screen2[b];
			dula=0;
			P0=0xff;
			wela=1;
			P0=choice[b];
			wela=0;
			for (j=100; j>0; j--);
		}
	}

}

void main (void)
{
	TMOD=0x01;  // timer 0 method 1
	TH0=(65536-45872)/256; // initialize timer 0
	TL0=(65536-45872)%256;
	EA=1;   // open all interrupt
	ET0=1;  // setup timer 0
	TR0=1; //start timer 0
	num=0;
	while(1)
	{
		show_screen1();
		while (op_switch == 0)
		{
			wela=1;
			P0=0xff;
			wela=0;
		}
		show_screen2();
		while (op_switch == 0)
		{
			wela=1;
			P0=0xff;
			wela=0;
		}
	}
}