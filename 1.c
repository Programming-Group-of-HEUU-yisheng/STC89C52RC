// bit method
/*
-----------------------
¹Ü 1 2 3 4 5 6 7 8
Î» 0 1 2 3 4 5 6 7
------------------------
*/

#include <reg52.h>

sbit led1=P1^0;
sbit led2=P1^2;
sbit led3=P1^4;
sbit led4=P1^6;

void main(void)
{
	led1=0;
	led2=0;
	led3=0;
	led4=0;
	while(1);  // stay here cause CPU is running
}