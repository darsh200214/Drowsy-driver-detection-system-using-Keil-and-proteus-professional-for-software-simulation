#include<REGX51.h>

sbit rs = P3^7;
sbit en = P3^6;

sbit EyeBlinkSensor = P1^0;

sbit Buzzer = P1^1;

sbit M11 = P1^2;
sbit M12 = P1^3;
sbit M21 = P1^4;
sbit M22 = P1^5;

int l;

void delay(unsigned char a)
{
	int i,j;
	for(i=0;i<a;i++)
	for(j=0;j<=1000;j++);
}

void Cmd(unsigned char a)
{
	rs=0;
	P2=a;
	en=1;
	delay(10);
	en=0;
}

void Data(unsigned char a)
{
	rs=1;
	P2=a;
	en=1;
	delay(10);
	en=0;
}

void String(unsigned char *p)
{
	while(*p)
		Data(*p++);
}		

void main()
{
	M11 = 0;
	M12 = 0;
	M21 = 0;
	M22 = 0;
	Buzzer = 0;
	Cmd(0x38);
	Cmd(0x0E);
	Cmd(0x80);
	String("  DROWSY DRIVER  ");
	Cmd(0xc0);
	String("DETECTING SYSTEM");
	delay(500);
	Cmd(0x01);
	while(1)
	{
		if(EyeBlinkSensor == 0)
		{
			Buzzer = 1;
			M11=0; M12=0; M21=0; M22=0;
			Cmd(0x80);
			String("  DRIVER  IS  ");
			Cmd(0xc0);
			String("  SLEEPING....  ");
			
		}	
		else
		{
			Buzzer = 0;
			M11=1; M12=0; M21=1; M22=0;
			Cmd(0x80);
			String("DRIVER IS NOT ");
			Cmd(0xc0);
			String("SLEEPING  ");
		}	
	}
}
	
