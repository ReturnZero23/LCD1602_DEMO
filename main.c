#include <msp430.h> 

/*
 * main.c
 */
char a[]="20121314";

void delay(int t)
{
	int s =500;
	for(;t>0;t--)
	{
		for(;s>0;s--)
		{
			;;
		}
	}
}

void write_com(char com)
{
	P1OUT &=~(1<<3);//RS=0高电平选择数据寄存器，低电平选择指令寄存器
	P1OUT &=~(1<<4);//R/W=0高电平为读，低电平为写
	P1OUT &=~(1<<5);//EN=0
	delay(8);
	P2OUT = com;
	delay(8);
	P1OUT |=(1<<5);//EN=1
	delay(8);
	P1OUT &=~(1<<5);//EN=0
}

void write_data(char data)
{
	P1OUT |=(1<<3);//RS=0高电平选择数据寄存器，低电平选择指令寄存器
	P1OUT &=~(1<<4);//R/W=0高电平为读，低电平为写
	P1OUT &=~(1<<5);//EN=0
	delay(8);
	P2OUT = data;
	delay(8);
	P1OUT |=(1<<5);//EN=1
	delay(8);
	P1OUT &=~(1<<5);//EN=0
}

void intitial_LCD1602()
{
		delay(20);
		write_com(0x38);
		delay(20);
		write_com(0x0c);
		delay(20);
		write_com(0x06);
		delay(20);
		write_com(0x01);
}

void Disp_LCD1602(char x,char y,char *str)
{
	char pos;
	switch(x)
	{
	case 0:pos = 0x80 + y;break;
	case 1:pos = 0xc0 + y;break;
	default:pos = 0x80;break;
	}
	write_com(pos);
	while(*str!=0)
	{
		write_data(*str);
		str++;
	}
}

int main(void) {
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
	char *pa;
	pa = a;

	P2SEL = 0x00;
	P2DIR |= 0Xff;
	P1DIR |= 0X38;
	intitial_LCD1602();
	for(;;)
	{
		Disp_LCD1602(1,2,pa);
		Disp_LCD1602(0,3,pa);
	}
	
	return 0;
}
