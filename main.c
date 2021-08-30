#include "DHT11.h"
#include "stm32f10x.h"                   

/*
kurulum
PB0 -> data pin
*/
float temp_0,hum_0;
uint8_t Rh_byte1, Rh_byte2, Temp_byte1, Temp_byte2;
uint16_t SUM;

float Temperature = 0;
float Humidity = 0;
uint8_t Presence = 0;


int main(void)
{
	// delayUs fonksiyonunun yüklenmesi için gerekli systick registerlari
	SysTick->CTRL = 0;
	SysTick->LOAD = 0x00FFFFFF;
	SysTick->VAL = 0;
	SysTick->CTRL = 5;
	RCC->APB2ENR |= 8; /// port B aktif



	
	while(1)
	{
	  DHT11_Start();
	  Presence = DHT11_Check_Response(); //yaniti kontrol et
	  Rh_byte1 = DHT11_Read ();//virgülden önceki deger (en yüksek basamakli)
	  Rh_byte2 = DHT11_Read ();//virgülden sonraki deger (en düsük basamakli)
	  Temp_byte1 = DHT11_Read ();
	  Temp_byte2 = DHT11_Read ();
	  SUM = DHT11_Read();//toplam deger

	/*	temp_0=Temp_byte2/10;//Sıcaklık ve Nem bilgisini float tipinde almak için
		hum_0 =Rh_byte2/10;

	  Temperature = (float) Temp_byte1+temp_0;
	  Humidity = (float) Rh_byte1+hum_0;*/
		DelayUs(2000000);//2sn 
	}
	
}

