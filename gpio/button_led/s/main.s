.equ LED, 0x02
.equ BUT, 0X07

.ORG 0X0000

START:
	LDI R16, 0B00000100 ;PD2 = OUT, rest is IN
	OUT DDRD, R16
	LDI R16, 0B11111111
	OUT PORTD, R16      ;enable pull-up for all registers

	NOP                 ;synchronize PORT data, when reading soon after a write op

MAIN:
	SBIC PIND, BUT      ;verify whetter the button was pressed
	RJMP MAIN

WAIT_RELEASE:
	SBIS PIND, BUT      ;if button not released, wait
	RJMP WAIT_RELEASE
	RCALL START_DELAY   ;"eliminate" noise

	SBIC PORTD, LED     ;toggle LED state
	RJMP ON
	SBI PORTD, LED      ;turn-off LED
	RJMP MAIN

ON:
	CBI PORTD, LED      ;turn-on LED
	RJMP MAIN

START_DELAY:
	CLR R3
	CLR R2
DELAY:
	DEC R3
	BRNE DELAY
	DEC R2
	BRNE DELAY
	RET	 
