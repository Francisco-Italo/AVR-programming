#ifndef _DEFS_H
#define _DEFS_H

#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/pgmspace.h>

#define SET_BIT(x,bt) (x|=(1<<bt))
#define CLR_BIT(x,bt) (x&=~(1<<bt))
#define TST_BIT(x,bt) (x&(1<<bt))
#define TGL_BIT(x,bt) (x^=(1<<bt))

#endif
