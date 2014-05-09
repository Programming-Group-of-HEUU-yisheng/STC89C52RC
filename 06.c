// Bus method - delay 500 ms

#include <reg52.h>

void delay(void)
{
	unsigned int i,j;
	for (i=500;i>0;i--)
		for (j=110;j>0;j--);
}

void main(void)
{
	while(1)
	{
		P1=0xfc;
		delay();
		P1=0xff;
		delay();
	}
}
