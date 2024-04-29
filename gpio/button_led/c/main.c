#include <avr/io.h>
#include <avr/delay.h>

#define TST_BIT(x,bt) (x & (1<<bt))
#define TGL_BIT(x,bt) (x ^= (1<<bt))

#define GLED PD4
#define YLED PC1
#define RLED PB0

#define BUT PD7

void seq_one();
void seq_two();
void seq_three();

int main(){
	DDRD = 1<<4;
	DDRC = 1<<1;
	DDRB = 1;

	PORTD = 0XFF;
	PORTC = 0XFF;
	PORTB = 0XFF;
	
	uint8_t count = 0;
	while(1){
		if(!TST_BIT(PIND,BUT)) count = (count+1)%4;
		
		switch(count){
                                case 1: seq_one();   break;
                                case 2: seq_two();   break;
                                case 3: seq_three(); break;
                }
                
		_delay_ms(50);
	}
	return 0;
}

void seq_one(){
	TGL_BIT(PORTB,RLED);
        _delay_ms(400);
        TGL_BIT(PORTC,YLED);
        _delay_ms(400);
        TGL_BIT(PORTD,GLED);
        _delay_ms(400);
}

void seq_two(){
	TGL_BIT(PORTD,GLED);
        _delay_ms(200);
        TGL_BIT(PORTC,YLED);
        _delay_ms(200);
        TGL_BIT(PORTB,RLED);
        _delay_ms(200);
}

void seq_three(){
	TGL_BIT(PORTC,YLED);
        _delay_ms(600);
        TGL_BIT(PORTB,RLED);
        _delay_ms(600);
        TGL_BIT(PORTD,GLED);
        _delay_ms(600);
}
