#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define SET_BIT(x,bt) (x|=(1<<bt))
#define CLR_BIT(x,bt) (x&=~(1<<bt))
#define TST_BIT(x,bt) (x&(1<<bt))
#define TGL_BIT(x,bt) (x^=(1<<bt))

#define RLED PB5
#define YLED PB4

ISR(INT0_vect);
ISR(INT1_vect);

int main()
{
	DDRD = 0X00;
	PORTD = 0XFF;
	DDRB = 0b00110000;
	PORTB = 0b11001111;

	UCSR0B = 0x00;

	EICRA = (1<<ISC11)|(1<<ISC10)|(1<<ISC01);
	EIMSK = (1<<INT1)|(1<<INT0);

	sei();

	for(;;);
}

ISR(INT0_vect)
{
	TGL_BIT(PORTB,RLED);
	_delay_ms(200);
}

ISR(INT1_vect)
{
	TGL_BIT(PORTB,YLED);
	_delay_ms(200);
}
