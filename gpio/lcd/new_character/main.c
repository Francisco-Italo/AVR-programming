#include "../inc/defs.h"
#include "../inc/lcd.h"

// caractere Ç
const unsigned char c1[] PROGMEM={
					0b01110,
					0b10001,
					0b10000,
					0b10000,
					0b10101,
					0b01110,
					0b10000
				};

// caractere delta 
const unsigned char c2[] PROGMEM={
					0b00100,
					0b00100,
					0b01010,
					0b01010,
					0b10001,
					0b11111,
					0b00000
				};
//-----------------------------------------------------------------------------------
//Rotina principal
//-----------------------------------------------------------------------------------
int main()
{
	unsigned char k;
	
	DDRD = 0xFF;
	DDRB = 0xFF;

	init_LCD_4bits();

	cmd_LCD(0x40,0);

	for(k=0;k<7;++k){
		cmd_LCD(pgm_read_byte(&c1[k]),1);
	}
	cmd_LCD(0x00,1);

	cmd_LCD(0x48,0);
	
	for(k=0;k<7;++k){
		cmd_LCD(pgm_read_byte(&c2[k]),1);
	}
	cmd_LCD(0x00,1);

	cmd_LCD(0x80,0);
	cmd_LCD(0x00,1);
	cmd_LCD(0x01,1);

	for(;;);
}

