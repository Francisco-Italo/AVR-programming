#include <avr/io.h>
#include <avr/eeprom.h>
#include "../gpio/lcd/inc/defs.h"
#include "../gpio/lcd/inc/lcd.h"

int main()
{
	DDRD = 0xF0;
	DDRB = 0x03;

	init_LCD_4bits();

	unsigned int uiAddr;
	unsigned int uiVal;
	unsigned char ucCheckBit = 0;
	
	write_LCD("Aguarde...");

	for(uiAddr = 0; uiAddr < 1024; ++uiAddr)
	{
		_EEPUT(uiAddr,0xAA);
	}

	for(uiAddr = 0; uiAddr < 1024; ++uiAddr)
	{
		_EEGET(uiVal,uiAddr);
		if(uiVal != 0xAA)
		{
			ucCheckBit = 1;
			break;
		}
	}

	cmd_LCD(0x01,0);
	_delay_ms(20);

	if(ucCheckBit)
	{
		write_LCD("Erro");
	}
	else
	{
		write_LCD("Sem erros");
	}

	for(;;);
	//return 0;
}
