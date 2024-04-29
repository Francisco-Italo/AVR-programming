#include <avr/io.h>
#include <avr/delay.h>

#define TGL_BIT(x,bt) (x ^= (1<<bt))
#define GLED 0X04	//pin 4
#define YLED 0X01	//pin 1
#define RLED 0x05	//pin 5

int main(){
	DDRB = 1<<5;	//mux pin 5 on port b to output
	DDRC = 1<<1;	//mux pin 1 on port c to output
	DDRD = 1<<4;	//mux pin 4 on port d to output
	
	while(1){
		TGL_BIT(PORTB,RLED);
		_delay_ms(900);
		TGL_BIT(PORTC,YLED);
                _delay_ms(600);
		TGL_BIT(PORTD,GLED);
                _delay_ms(200);
	}
	return 0;
}
