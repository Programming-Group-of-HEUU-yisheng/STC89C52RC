// eight flashing LEDs show 8-bit binary plus progress

//method1: for from 0 to 255 (256)

#include <reg52.h>
#define uint unsigned int

uint i;

void delayms (uint xms)
{
	uint i,j;
	for (i=xms; i>0; i--)
		for (j=110; j>0; j--);
}

void main (void)
{
	for (i=0; i<256; i++)
	{
		P1=~i;
		delayms(200);
	}
}


//simple method

// use WHILE to determine when we quit

#include <reg52.h>
#define uint unsigned int

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
		P1=0xff;
		delayms(400);
		while(P1)
		{
			P1--;
			delayms(500);
		}
	}
}
