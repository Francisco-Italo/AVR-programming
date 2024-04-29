#include "../inc/defs.h"
#include "../inc/lcd.h"

//prototypes
void create_charac();
void write_num(unsigned char adr, unsigned char nr);

// info for new character creation
const unsigned char new_charac[] PROGMEM={
						0b00000001,0b00000001,0b00000001,0b00000001,0b00000001,0b00000001,0b00011111, //0
						0b00011111,0b00010000,0b00010000,0b00010000,0b00010000,0b00010000,0b00010000, //1
						0b00011111,0b00000001,0b00000001,0b00000001,0b00000001,0b00000001,0b00000001, //2
						0b00000001,0b00000001,0b00000001,0b00000001,0b00000001,0b00000001,0b00000001, //3
						0b00011111,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00011111, //4
						0b00011111,0b00000001,0b00000001,0b00000001,0b00000001,0b00000001,0b00011111, //5
						0b00011111,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000, //6
						0b00011111,0b00010000,0b00010000,0b00010000,0b00010000,0b00010000,0b00011111  //7
					};
// code to form the numbers from 0 to 9 such that one umber occupies one lcd column cell
const unsigned char big_num[10][4] PROGMEM={ 
						{0x01, 0x02, 0x4C, 0x00}, //nr. 0
						{0x20, 0x7C, 0x20, 0x7C}, //nr. 1
						{0x04, 0x05, 0x4C, 0x5F}, //nr. 2
						{0x06, 0x05, 0x5F, 0x00}, //nr. 3
						{0x4C, 0x00, 0x20, 0x03}, //nr. 4
						{0x07, 0x04, 0x5F, 0x00}, //nr. 5
						{0x07, 0x04, 0x4C, 0x00}, //nr. 5
						{0x06, 0x02, 0x20, 0x03}, //nr. 7
						{0x07, 0x05, 0x4C, 0x00}, //nr. 8
						{0x07, 0x05, 0x20, 0x03}  //nr. 9
					};

//-----------------------------------------------------------------------------------
//Rotina principal
//-----------------------------------------------------------------------------------
int main()
{
	DDRD = 0XFF;
	DDRB = 0XFF;

	init_LCD_4bits();
	create_charac();

	while(1)
	{
		write_num(0x80,0);
		write_num(0x82,1);
		write_num(0x85,2);
		write_num(0x88,3);
		write_num(0x8B,4);
		write_num(0x8E,5);

		_delay_ms(3000);

		cmd_LCD(0x01,0);
		
		_delay_ms(1000);

		write_num(0x80,6);
		write_num(0x83,7);
		write_num(0x86,8);
		write_num(0x89,9);
		write_num(0x8B,1);
		write_num(0x8D,0);

		_delay_ms(3000);
	
		cmd_LCD(0x01,0);
	
		_delay_ms(1000);
	}

}

void create_charac()
{
	unsigned char i,k,j=0,n=0x40;
	for(i=0;i<8;++i)
	{
		cmd_LCD(n,0);
		for(k=0;k<7;++k)
		{
			cmd_LCD(pgm_read_byte(&new_charac[k+j]),1);
		}
		cmd_LCD(0x00,1);

		j+=7;
		n+=8;
	}
}

void write_num(unsigned char adr, unsigned char nr)
{
	cmd_LCD(adr,0);
	cmd_LCD(pgm_read_byte(&big_num[nr][0]),1);
	cmd_LCD(pgm_read_byte(&big_num[nr][1]),1);
	cmd_LCD(adr+64,0);
	cmd_LCD(pgm_read_byte(&big_num[nr][2]),1);
	cmd_LCD(pgm_read_byte(&big_num[nr][3]),1);

}
