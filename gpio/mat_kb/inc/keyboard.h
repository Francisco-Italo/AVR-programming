#ifndef _KEYBOARD_H
#define _KEYBOARD_H

#include "../../lcd/inc/defs.h"

#define LINE PIND
#define COL PORTD

unsigned char read_keyboard();

#endif
