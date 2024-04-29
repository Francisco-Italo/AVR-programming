#include "../lcd/inc/defs.h"
#include "../lcd/inc/lcd.h"
#include "inc/keyboard.h"

const unsigned char msg1[] PROGMEM = "Teclado 4x4\0";
const unsigned char msg2[] PROGMEM = "Tecla = \0";

int main()
{
	DDRB = 0xFF;
	DDRD = 0x0F;

	PORTD = 0xFF;

	UCSR0B = 0x00;

	init_LCD_4bits();
	write_LCD_Flash(msg1);
	cmd_LCD(0xC7,0);
	write_LCD_Flash(msg2);

	unsigned char key;

	while(1)
	{
		key = read_keyboard();
		if(key != 0xFF)
		{
			cmd_LCD(0xCF,0);
			cmd_LCD(key,1);
		}
	}
}
