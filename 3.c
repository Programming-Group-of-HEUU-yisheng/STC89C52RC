// bit method
/*
-----------------------
¹Ü 1 2 3 4 5 6 7 8
Î» 0 1 2 3 4 5 6 7
-----------------------
*/
#include <reg52.h>

sbit led1=P1^1;
sbit led2=P1^3;
sbit led3=P1^4;
sbit led4=P1^5;

void main(void)
{
	led1=0;
	led2=0;
	led3=0;
	led4=0;
	while(1);
}