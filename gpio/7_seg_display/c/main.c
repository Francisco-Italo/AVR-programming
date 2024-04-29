#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/pgmspace.h>

#define TST_BIT(x,bt) (x & (1<<bt))

#define DISPLAY PORTD
#define BUT PB0

const unsigned char table[] PROGMEM = 
{0x40,0x79,0x24,0x30,0x19,0x12,0x02,0x78,0x00,0x18,0x08,0x03,0x46,0x21,0x06,0x0E};

int main(){
	unsigned char value = 0;

	DDRB = 0b1111110;
	PORTB = 0x01;
	DDRD = 0xFF;
	UCSR0B = 0x00;

	while(1){
		if(!TST_BIT(PINB,BUT)){
			if(value == 0x0F) value = 0;
			else value++;
		}
		DISPLAY = pgm_read_byte(&table[value]);
		_delay_ms(100);
	}
	return 0;
}
