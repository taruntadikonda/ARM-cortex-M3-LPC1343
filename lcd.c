/*port2_2,3,4,5(data)   2.6-RS 2.7-E*/
/*port1_8,9,10,11(data) 3.0-RS 3.1-E*/

#include"lpc13xx.h"
//#include"sys.h"

void delay(int j)
{
	int i=0;
	for(i=14400*j;i>0;i--);
}
void nibble(unsigned int i)
{
 delay(3);
 LPC_GPIO1->MASKED_ACCESS[(0X0F<<8)]=((i&0x0F)<<8);
 LPC_GPIO3->MASKED_ACCESS[(1<<1)]=(1<<1);
 LPC_GPIO3->MASKED_ACCESS[(1<<1)]=0;
}

void byte(unsigned char c)
{
nibble(c>>4);
nibble(c);
}

void cmd(unsigned char c)
{
 LPC_GPIO3->MASKED_ACCESS[(1<<0)]=0;//rs=0 cmd
 byte(c);
}

void data(unsigned char c)
{
 LPC_GPIO3->MASKED_ACCESS[(1<<0)]=(1<<0);//rs=1 data
 byte(c);
}

void str(unsigned char* l)
{
 while(*l!='\0')
 {
 data(*l++);
}
}

void position(int x, int y)
{
 if(y==0)
 cmd((1<<7)+0x00+x);
 if(y==1)
 cmd((1<<7)+0x40+x);
 if(y==2)
 cmd((1<<7)+0x14+x);
 if(y==3)
 cmd((1<<7)+0x54+x);
}

void lcd_init(void)
{
 LPC_SYSCON->SYSAHBCLKCTRL|=(1<<16);//iocon
 LPC_GPIO1->DIR|=((1<<8)|(1<<9)|(1<<10)|(1<<11));//((0X3F)<<2);//PORT2.2-7
 LPC_GPIO3->DIR|=((1<<0)|(1<<1));	
 LPC_GPIO3->MASKED_ACCESS[(1<<0)]=0;
 LPC_GPIO3->MASKED_ACCESS[(1<<1)]=0;
 delay(16);
 nibble(0x03);
 delay(5);
 nibble(0x03);
 delay(100);
 nibble(0x03);
 nibble(0x02);
 cmd(0x28);//4-bit mode
 cmd(0x08);//display off
 cmd(0x01);//clear screen
 //cmd(0x02);
 cmd(0x06);//auto increment
 cmd(0x0C);//cursor blinking
}
void clrscr(void)
{
 cmd(0x01);
}
void scroll(unsigned char* l, int y)
{
int j=0,i=0,r=30;
while(l[j]!='\0')
{
 j=j+1;
}
while(r>=0)
{
position(i,y);
str(l);
delay(400);
clrscr();
i=i+1;
if(i==20)
i=0;
r=r-1;
}
}


					 