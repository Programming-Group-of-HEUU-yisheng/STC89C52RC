// bit method - delay 500ms

/*
-----------------------
¹Ü 1 2 3 4 5 6 7 8
Î» 0 1 2 3 4 5 6 7
------------------------
*/

#include <reg52.h>

sbit led1=P1^0;
sbit led2=P1^1;

void delay(void)
{
	unsigned int i,j;
	for (i=500;i>0;i--)     // change this value to change delay time
		for (j=110;j>0;j--);
}

void main(void)
{
	while(1)    // stay in the loop
	{
		led1=0;
		led2=0;
		delay();
		led1=1;
		led2=1;
		delay();
	}
}