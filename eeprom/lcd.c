#include "../gpio/lcd/inc/lcd.h"

//-----------------------------------------------------------------------------------
// Sub-rotina para enviar caracteres e comandos ao LCD com via de dados de 4 bits
//-----------------------------------------------------------------------------------
void cmd_LCD(unsigned char data, char type)
{
	DATA_LCD = data;

	// type=0->instrução;type=1->dado
	type == 0 ? CLR_BIT(CTRL_LCD,RS) : SET_BIT(CTRL_LCD,RS);

	// primeiro nibble - 4 MSB
	#if(NIBBLE)
		DATA_LCD = (DATA_LCD & 0x0F) | (0xF0 & data);
	#else
		DATA_LCD = (DATA_LCD & 0xF0) | (data >> 4);
	#endif

	pulse_en();

	// segundo nibble de dados - 4 LSB
	#if(NIBBLE)
		DATA_LCD = (DATA_LCD & 0x0F) | (0xF0 & (data << 4));
	#else
		DATA_LCD = (DATA_LCD & 0xF0) | (0x0F & data);
	#endif

	pulse_en();

	// caso seja instrução de limpeza ou retorno de cursor
        if(type == 0 && data < 4)
        {
                _delay_ms(2);
        }
}
//-----------------------------------------------------------------------------------
//Sub-rotina para inicialização do LCD com via de dados de 4 bits
//-----------------------------------------------------------------------------------
void init_LCD_4bits()
{
	CLR_BIT(CTRL_LCD,RS);
	CLR_BIT(CTRL_LCD,E);

	_delay_ms(45);

	// interface de 8 bits
	#if (NIBBLE)
		DATA_LCD = (DATA_LCD & 0x0F) | 0x30;
	#else
		DATA_LCD = (DATA_LCD & 0xF0) | 0x03;
	#endif

	pulse_en();
	_delay_ms(5);
	pulse_en();
	_delay_us(200);
	pulse_en();

	// interface de 4 bits
	#if (NIBBLE)
		DATA_LCD = (DATA_LCD & 0x0F) | 0x20;
	#else
		DATA_LCD = (DATA_LCD & 0xF0) | 0x02;
	#endif

	pulse_en();

	cmd_LCD(0x28,0);	// interface de 4 bits e 2 linhas
	cmd_LCD(0x08,0);	// desliga display
	cmd_LCD(0x01,0);	// limpa display
	cmd_LCD(0x0C,0);	// mensagem aparente cursor inativo não piscando
	cmd_LCD(0x80,0);	// inicializa cursor na primeira posição à esquerda - 1ª linha
}
//------------------------------------------------------------------------------------
//Sub-rotina de escrita no LCD - dados armazenados na RAM
//------------------------------------------------------------------------------------
void write_LCD(char *c)
{
	for (; *c != 0; ++c) cmd_LCD(*c,1);
}
//------------------------------------------------------------------------------------
//Sub-rotina de escrita no LCD - dados armazenados na FLASH
//------------------------------------------------------------------------------------
void write_LCD_Flash(const char *c)
{
	for (; pgm_read_byte(&(*c)) != 0; ++c) cmd_LCD(pgm_read_byte(&(*c)),1);
}
//------------------------------------------------------------------------------------
//Conversão de um número em seus digitos individuais – função auxiliar
//------------------------------------------------------------------------------------
void ident_num(unsigned int vl, unsigned char *disp)
{
	unsigned char n;

	for(n = 0; n < VECTOR_SIZE; ++n)
	{
		disp[n] = 0 + CONV_ASCII;	// limpa vetor para armazenagem dos dígitos
	}

	do
	{
		*disp = (vl%10) + CONV_ASCII;
		vl /= 10;
		disp++;
	}while(vl != 0);
}
