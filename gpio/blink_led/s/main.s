.equ LED, 0X05   ;macro definition
.ORG 0x000       ;flash's first address memory for code write

START:
	LDI R16, 0XFF
	OUT DDRB, R16		;pin 5 of portb is in output mode
MAIN:
	SBI PORTB, LED		;put 5v on PB5
	RCALL DELAY		;call delay sub-routine
	CBI PORTB, LED		;put 0v on PB5
	RCALL DELAY
	RJMP MAIN		;unconditional jump to MAIN

DELAY:
	LDI R17, 0X00
	LDI R18, 0X00
	LDI R19, 0X00
	LDI R20, 0X00
BACK:
	DEC R17			;decrement in 1 unit register value
	BRNE BACK		;jump to BACK label when register not zero
	DEC R18
	BRNE BACK
	DEC R19
	BRNE BACK
	DEC R20
	BRNE BACK
	RET
