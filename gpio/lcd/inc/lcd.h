#ifndef _LCD_H
#define _LCD_H

#include "defs.h"

#define pulse_en() _delay_us(1);SET_BIT(CTRL_LCD,E); \
                _delay_us(1);CLR_BIT(CTRL_LCD,E); \
                _delay_us(45)

//Adaptation from 8-bit mode to 4-bit mode
/*
#define DATA_LCD PORTD
#define CTRL_LCD PORTB
#define RS PB0
#define E PB1

#define NIBBLE          1       //0 para via de dados do LCD nos 4 LSBs do PORT
                                //empregado (Px0-D4, Px1-D5, Px2-D6, Px3-D7), 1 para via de
                                //dados do LCD nos 4 MSBs do PORT empregado 
                                //(Px4-D4, Px5-D5,Px6-D6, Px7-D7)
*/

//Rearrangement to PORTB
#define DATA_LCD PORTB
#define CTRL_LCD PORTB
#define RS PB4
#define E PB5

#define NIBBLE          0

#define VECTOR_SIZE     5       // número de digitos individuais para a conversão por ident_num()
#define CONV_ASCII      48      // 48 se ident_num() deve retornar um número no formato ASCII (0 para formato normal)

//protótipos das funções
void cmd_LCD(unsigned char data, char type);
void init_LCD_4bits();
void write_LCD(char *c);
void write_LCD_Flash(const char *c);
void ident_num(unsigned int vl, unsigned char *disp);

#endif
