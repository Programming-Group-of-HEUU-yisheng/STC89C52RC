/*
	This is the INTERRUPT version, we using timer interrupt in the 8051 mcu
		to make it accurate when display something
	The interrupt part only have timer initialization, and put other statement
		into main() or sub-functions
	
	something we should know
	- EA...interrupt enable
	- ET0... Timer 0 
	
	TODO:
	- abandon FLAG part for check purpose   ... maybe we will find a better way
	- display part
			How to change screen to another one

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


bit op_scr=1;
bit op_switch=1;
*/
bit op;
/*
	define what we will display 
	screen1...11-d-1
	screen2...050118
	choice...from left to right, for dynamic display purpose only
		uchar code choice[]={0xfe,0xfd,0xfb,0xf7,0xef,0xdf}
*/

uchar code screen1[]={0x06,0x06,0x40,0x5e,0x40,0x06};
uchar code screen2[]={0x3f,0x6d,0x3f,0x06,0x06,0x7f};
uchar code choice[]={0xfe,0xfd,0xfb,0xf7,0xef,0xdf};

uchar num_t0;

void delayms (uint ms)
{
	uint i,j;
	for (i=ms; i>0; i--)
		for (j=110; j>0; j--);
}

/*
ABANDON
        0     1000     2000   3000   4000
scr           
switch  
num     0       20       40     60     80 
*/
void T0_timer() interrupt 1
{
	// 1 sec
	TH0=(65536-45872)/256;  //50 ms
	TL0=(65536-45872)%256;
	num_t0++;
	if (num_t0 ==20)
	{
		wela=1;
		P0=0xff;
		wela=0;
		
		if (num_t0 == 40)
		{
			op=0;
			if (num_t0 == 60)
			{
				wela=1;
				P0=0xff;
				wela=0;
				
				if (num_t0 == 80)
				{
					op=1;
					num_t0=0;
				}
			}
		}
	}
}

void display (bit op)
{
	uchar i;
	if (op == 1)
	{
		for (i=0; i<6; i++)
		{
			dula=1;
			P0=screen2[i];
			dula=0;
			P0=0xff;
			wela=1;
			P0=choice[i];
			wela=0;
			delayms(50);
		}
	}
	else
	{
		for (i=0; i<6; i++)
		{
			dula=1;
			P0=screen1[i];
			dula=0;
			P0=0xff;
			wela=1;
			P0=choice[i];
			wela=0;
			delayms(50);
		}
	}
}

void init (void)
{
	TMOD=0x01;  // timer 0 method 1 
	TH0=(65536-45872)/256; // initialize timer 0
	TL0=(65536-45872)%256;
	EA=1;   // open all interrupt
	ET0=1;  // setup timer 0
	TR0=1; //start timer 0
	num_t0=0;
	op=1;
}

void main (void)
{
	init();
	while(1)
	{
		display(op);
	}
}
