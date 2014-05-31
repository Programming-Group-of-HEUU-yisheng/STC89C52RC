// eight flashing LEDs£¬delay 100ms with beep sound
// beep.......P2^3

// two FOR control number
#include <reg52.h>
#include <intrins.h>

#define uint unsigned int
#define uchar unsigned char

sbit beep=P2^3;

uint i;
uchar aa;

void delayms (unsigned int xms)
{
	uint i,j;
	for (i=xms; i>0; i--)
		for (j=110; j>0; j--);
}

void main (void)
{
	while(1)
	{
		aa=0xfe;
		// left flashing part
		for (i=0; i<7; i++)
		{
			P1=aa;
			beep=0;
			aa=_crol_(aa, 1);   // left LIB function
			delayms(100);
			P1=0xff;
			beep=1;
			delayms(200);
		}
		aa=0x7f;
		// right flashing part
		for (i=0; i<7; i++)
		{
			P1=aa;
			beep=0;
			aa=_cror_(aa, 1);
			delayms(100);
			P1=0xff;
			beep=1;
			delayms(200);
		}
	}
}
