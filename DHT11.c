#include "stm32f10x.h" 
#include "DHT11.h" 

void DelayUs(unsigned long t)
{
	for(;t>0;t--)
		{
		 SysTick->LOAD = 36;
	   SysTick->VAL = 0;
	   while((SysTick->CTRL & 0x00010000) == 0);
		}
}

void DHT11_Start(){
	  GPIOB->CRL  = 0x00000003; /// PA3 output
	  GPIOB->ODR  = 0x0;
	 	DelayUs(18000);//20ms
		GPIOB->ODR  = 0x10;
	  DelayUs(20);
	  GPIOB->CRL  = 0x00000004; /// PA3 input
}

int DHT11_Check_Response (void)
{
	uint8_t Response = 0;
	DelayUs (80);
	if (!(GPIOB->IDR & 0x00000001))// pb0 0 ise
	{
		DelayUs (80);
		if ((GPIOB->IDR & 0x00000001)) Response = 1;// pb0 1 ise
		else Response = -1; // 255
	}
	while ((GPIOB->IDR & 0x00000001));   // wait for the pin to go 0

	return Response;
}

int DHT11_Read (void)
{
	uint8_t i,j;
	for (j=0;j<8;j++)
	{
		while (!(GPIOB->IDR & 0x00000001));   // wait for the pin to go high
		DelayUs (40);   // wait for 40 us
		if (!(GPIOB->IDR & 0x00000001))   // if the pin is low
		{
			i&= ~(1<<(7-j));   // write 0
		}
		else i|= (1<<(7-j));  // if the pin is high, write 1
		while ((GPIOB->IDR & 0x00000001));  // wait for the pin to go low
	}
	return i;
}
