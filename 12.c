/*
		Author: wongsyrone
		Object: 
				use T0 and T1 ring the beep 
				T0 ... freq.   ...  use different initial number to change freq.
				T1 ... duration of each freq.  ...  to keep a whole wave of 1 Hz we use 2000 ms for the duration of each freq.
				output frequency 1, 10, 50, 100, 200, 400, 800, 1000 Hz one by one
				with 300ms delay
		Problems: 
				1. ���Ʒ���������������������ʣ���������õġ�������Ƶ�ʷ�Χ�ǣ�20Hz ��20kHz����Ŀ�е� 1Hz��10Hz��������������
				2. һ�����300ms����ͬһ��Ƶ�� ��ʱ���أ���500Hz ��ʱ�䳤�ȡ�����˵��ÿ��Ƶ��ʱ�䳤�ȶ���300ms���м�û�м�����������������1Hz������Ϊ1s�����ܶ�500ms�ˣ�300ms�����á�����300msֻ������Ƶ��֮����ɵĿհװɡ�
				3. ������ �Ǹߵ�ƽ ���� ����  �͵�ƽ ������Ƶ�ʹ���֮��Ŀհ���ֹͣ�����������ǲ��ܣ�
				4. ��� 1KHz��Ƶ�ʽ����󣬸���Σ���ֹͣ ���� ѭ����
				5. ϵͳ �����Ƕ����أ�
		Info: 
				T0 initial number ... 
				T1 initial number 
				
		TODO:
				- maybe we can try method 2 to initial N value automatically 
*/

#include <reg52.h>

#define uchar unsigned char
#define uint unsigned int

uchar code freq[]={};  // freq num array
//sbit beep=P2^3;

sbit beep=P1^0;    // just for not disturbing others

uchar k;       // for timer 
uint value_N;  // for different freq. initial number 
uint border;   // for duration of each freq.

/*
	NOTE:
			using 1.085069444 to calculate value N
			using 1.09 to calculate value N, and the results are in the ( )
		freq.(Hz)      cycle(ms)   semi-cycle(ms)  time wanted  value_N      multiple
		1             1000         500            500 000      X              800            
		10             100         50              50 000    46080(45872)     80         
		50             20          10              10 000    9216(9174)       16          
		100            10           5               5 000     4608(4587)       8     
		200             5           2.5             2 500     2304(2294)       4         
		400            2.5          1.25            1 250     1152(1147)       2        
		800            1.25        0.625              625      576(573)        1         
		1000            1          0.5                500      461(423)        -          
		                            ^                                                       
		                            |                                                        
		                  use this column 
	- To Be Researched
	1. There is a serious problem that when the multipler comes big, the time is not accurate as expected
	maybe we should try to initial timer with different value to avoid the issue
	
	2. <=10ms using method 2 to make it accurate (?)
*/
void T0_timer() interrupt 1
{
	// which freq. we should show, that is what cycle time should be
	TH0=(65536-
	TL0=(65536-
	
}

void T1_timer() interrupt 3
{
	// duration of each freq.
	// every freq. last 2000 ms  2000 * 8 = 16000 ms = 16 s 
	TH1=(65536-50000)/256;  //  50ms * 320
	TL1=(65536-50000)%256;
	

}

void init (void)
{
	TMOD=0x11;  // timer 0 and 1 both are in method 1
	TH0=(65536-
	TL0=(65536-
	TH1=(65536-
	TL1=(65536-
	EA=1;
	ET0=1;
	ET1=1;
	TR0=1;
	TR1=1;
	
	num0=0;
	num1=1;
}

void main (void)
{
	init();
	while(1)
	{
		
	}
}

/*
		a example on web
		
///////////////////////////////////////////////////////////////////
//////////
////////                maybe something wrong 
//////////
///////
///////////////////////////////////////////////////////////////////


#include<reg52.h>  
#include <intrins.h> 
#define uint unsigned int    
#define uchar unsigned char  
sbit beep=P2^3;
uchar tt;
uint fre,flag;

void main()		  
{
	fre=50000;
	beep=0;
	TMOD=0x11;//���ö�ʱ��0,��ʱ��1Ϊ������ʽ1
	TH0=(65536-fre)/256;
	TL0=(65536-fre)%256;
	TH1=(65536-50000)/256;
	TL1=(65536-50000)%256;
	EA=1;//�����ж�
	ET0=1;//����ʱ��0�ж�
	ET1=1;
	TR1=1;
	TR0=1;//������ʱ��0
	while(1);//�ȴ��жϲ���
	
}

void timer0() interrupt 1   //��ʱ��0�ж�
{
	TR0=0;    //���жϺ��ȰѶ�ʱ��0�жϹرգ���ֹ�ڲ�������������ж϶�ʧ
	TH0=(65536-fre)/256;
	TL0=(65536-fre)%256;
	tt++;
	if(flag<40)    //���¼���if�ֱ�����ѡȡ��ͬ��Ƶ��
		if(tt==10)
			{
				tt=0;
				fre=50000;
				beep=~beep;
			}
	if(flag>=40&&flag<80)
		{
			tt=0;
			fre=50000;
			beep=~beep;	
		}
	if(flag>=80&&flag<120)
		{
			tt=0;
			fre=10000;
			beep=~beep;	
		}
	if(flag>=120&&flag<160)
		{
			tt=0;
			fre=5000;
			beep=~beep;	
		}
	if(flag>=160&&flag<200)
		{
			tt=0;
			fre=2500;
			beep=~beep;	
		}
	if(flag>=200&&flag<240)
		{
			tt=0;
			fre=1250;
			beep=~beep;	
		}
	if(flag>=240&&flag<280)
		{
			tt=0;
			fre=625;
			beep=~beep;	
		}
	if(flag>=280&&flag<320)
		{
			tt=0;
			fre=312;
			beep=~beep;	
		}
	if(flag>=320&&flag<360)
		{
			tt=0;
			fre=156;
			beep=~beep;	
		}
	TR0=1;
}
void timer1() interrupt 3  //��ʱ��1�ж���������2��ʱ�䶨ʱ
{
	TH1=(65536-50000)/256;
	TL1=(65536-50000)%256;
	flag++;
	if(flag==360)
	  {
	    flag=0;
	    fre=50000;
	  }
}

*/
