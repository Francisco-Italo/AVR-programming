#include "../inc/defs.h"
#include "../inc/lcd.h"

const unsigned char msg[] PROGMEM = " DADOS de 4BITS!\0";	// mensagem na flash

//-----------------------------------------------------------------------------------
//Rotina principal
//-----------------------------------------------------------------------------------
int main()
{	/*
	DDRD = 0xF0;		// PORTD como saída
	DDRB = 0x03;		// PORTB como saída
	*/
	DDRB = 0x3F;

	init_LCD_4bits();

	write_LCD("  INTERFACE DE");		// string na RAM
	cmd_LCD(0xC0,0);			// desloca cursor para segunda linha
	write_LCD_Flash(msg);			// string armazenada na flash

	for(;;);
}
