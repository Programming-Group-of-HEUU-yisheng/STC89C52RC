/*
	Seriel port RX and TX
	Author: wongsyrone
	Object: send X to MCU and returns "NUMBER I get X" 
			using 9600bps or other buadrate
			NUMBER ... from 0 to 255
	Problem: When receive on PC, I get ASCII code 
		    we can send data using character or HEX, and HEX is recommended
		    we can receive HEX, it will be good, when receive character, it will be ASCII code
	TODO:  Find a better way to receive ASCII character from 0 to 255 
*/

#include <reg52.h>

#define uchar unsigned char
#define uint unsigned int

uchar code table[]="I get ";   // 6 characters

uchar flag,i,a;  
/* flag ... whether we should send or receive
    k ... NUMBER from 0 to 255
    i ... loop operator
    a ... SBUF
*/

void init ()
{
    /* TMOD controls timers behaviour */
	TMOD=0x20;
	/* buadrate set to 9600bps */
	TH1=0xfd;
	TL1=0xfd;
	/* Timer 1 controls buadrate */
	TR1=1;
	/* SMOD and interrupt configuration */
	REN=1;
	SM0=0;
	SM1=1;
	EA=1;  // all interrupt enable
	ES=1;  // seriel enable
}

void main (void)
{
	uchar k;
	init();
	k=0;
	while(1)
	{
		if (flag == 1)
		{
			ES=0;
			k++;
			if (k == 256) k=0;    // when get to 256 it flows
			
			SBUF=k;
			while(!TI);
			TI=0;
			
			for (i=0; i<6; i++)
			{
				SBUF=table[i];
				while(!TI);
				TI=0;
			}
			
			SBUF=a;
			while(!TI);
			TI=0;
            //   debug purpose   send <LF> character to PC
			/*
			SBUF='\n';      
			while(!TI);
			TI=0;
			*/
			ES=1;
			flag=0;
		}
	}
}

void seriel () interrupt 4
{
	RI=0;
	a=SBUF;
	flag=1;
}

