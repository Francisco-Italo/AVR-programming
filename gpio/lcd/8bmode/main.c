#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/pgmspace.h>

#define SET_BIT(x,bt) (x|=(1<<bt))
#define CLR_BIT(x,bt) (x&=~(1<<bt))
#define TST_BIT(x,bt) (x&(1<<bt))
#define TGL_BIT(x,bt) (x^=(1<<bt))

#define pulse_en() _delay_us(1);SET_BIT(CTRL_LCD,E); \
       		_delay_us(1);CLR_BIT(CTRL_LCD,E); \
		_delay_us(45)

#define DATA_LCD PORTD
#define CTRL_LCD PORTB
#define RS PB1
#define E PB0

const unsigned char msg1[] PROGMEM = "ABCDEFGHIJKLMNOP";
const unsigned char msg2[] PROGMEM = "QRSTUVXYZ 123456";

//-----------------------------------------------------------------------------------
//Sub-rotina para enviar caracteres e comandos ao LCD
//-----------------------------------------------------------------------------------
void cmd_LCD(unsigned char data, char type)
{
	DATA_LCD = data;
	
	// type=0->instrução;type=1->dado
	type == 0 ? CLR_BIT(CTRL_LCD,RS) : SET_BIT(CTRL_LCD,RS);

	pulse_en();

	// caso seja instrução de limpeza ou retorno de cursor
	if(type == 0 && data < 4)
	{
		_delay_ms(2);
	}
}
//-----------------------------------------------------------------------------------
//Sub-rotina de inicialização do LCD
//-----------------------------------------------------------------------------------
void init_LCD_8bit_mode()
{
	CLR_BIT(CTRL_LCD,RS);
	_delay_ms(15);		// estabilização do lcd
	
	DATA_LCD = 0x38;	// interface 8 bits, 2 linhas, matriz 7x5 pontos

	pulse_en();
	_delay_ms(5);

	pulse_en();
	_delay_us(200);

	pulse_en();
	pulse_en();

	cmd_LCD(0x08,0);	// desliga lcd
	cmd_LCD(0x01,0);	// limpa todo o display
	cmd_LCD(0x0C,0);	// mensagem aparente cursor inativo não piscando
	cmd_LCD(0x80,0);	// escreve na primeira posição a esquerda - 1ª linha
}
//-----------------------------------------------------------------------------------
//Sub-rotina de escrita no LCD
//-----------------------------------------------------------------------------------
void write_LCD(char *c)
{
	for (; *c != 0; ++c)
	{
		cmd_LCD(*c,1);
	}
}
//-----------------------------------------------------------------------------------
//Rotina principal
//-----------------------------------------------------------------------------------
int main()
{
	unsigned char i;

	DDRB = 0XFF;		// PORTB como saída
	DDRD = 0XFF;		// PORTD como saída
	UCSR0B = 0X00;		// habilita os pinos PD0 e PD1 como I/O

	init_LCD_8bit_mode();
	
	// impressão de msg1
	for(i = 0; i < sizeof(msg1)/sizeof(msg1[0]); ++i)
	{
		cmd_LCD(pgm_read_byte(&msg1[i]),1);	
	}

	cmd_LCD(0xC0,0);	// muda o cursor para a segunda linha

	// impressão de msg2
	for(i = 0; i < sizeof(msg2)/sizeof(msg2[0]); ++i)
	{
		cmd_LCD(pgm_read_byte(&msg2[i]),1);
	}

	for(;;);
}
