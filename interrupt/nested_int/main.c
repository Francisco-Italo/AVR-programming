#include "defs.h"

ISR(INT0_vect);
ISR(INT1_vect);

int main()
{
	DDRD = 0b11000000;
	PORTD = 0xFF;

	UCSR0B = 0x00;

	EICRA = 0b0000;
	EIMSK = (1<<INT1)|(1<<INT0);

	sei();

	while(1)
	{
		TGL_BIT(PORTD,RLED);
	}
}

ISR(INT0_vect)
{
	unsigned char sreg;
	sreg = SREG;

	CLR_BIT(EIMSK,INT0);

	sei();

	TGL_BIT(PORTD,YLED);
	_delay_ms(300);

	SET_BIT(EIMSK,INT0);

	SREG = sreg;
}

ISR(INT1_vect)
{
	TGL_BIT(PORTD,YLED);
	_delay_ms(200);
}
