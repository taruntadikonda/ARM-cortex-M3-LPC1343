#include "lpc13xx.h"
#include "lcd.h"
void adc()
{
	LPC_SYSCON->SYSAHBCLKCTRL |=(1<<6)|(1<<13)|(1<<16);
	LPC_SYSCON->PDRUNCFG &=~(1<<4);       //powering on the ADC
	LPC_IOCON->JTAG_TDI_PIO0_11 |=(1<<1);   //accesing as adc0
	LPC_IOCON->JTAG_TDI_PIO0_11 &=~(1<<7);		//enabling a analog pin
	LPC_ADC->CR|=(1<<0);								//using adc0;
	LPC_ADC->CR|=(1<<8)|(1<<12);	//clock divided by 18 so 17 should be writen. so 17 binnary value is 10001
	LPC_ADC->CR|=(1<<16);					//burst mode;
}
int main()
{
	
	int a,b;
	float analog;
	char c[10];
	SystemInit();
	adc();
	
	
	lcd_init();
	while(1)
	{
		while(!(LPC_ADC->STAT & (1<<0)));
		a=((LPC_ADC->DR0>>6)&(0x3FF));
		analog=(float)((a*3.3)/1023);
		sprintf(c,"%f",analog);
		clrscr();
		position(0,0);
		str(c);
		for(b=100000;b>0;b--);
		
	}
return 0;
}
