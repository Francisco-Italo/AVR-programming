#include "inc/keyboard.h"

/*C1 C2 C3 C4
  x  x  x  x  L1
  x  x  x  x  L2
  x  x  x  x  L3
  x  x  x  x  L4

PORT = C1 C2 C3 C4 L1 L2 L3 L4  (LSB -> C1 and MSB -> L4)
*/
const unsigned char kb[4][4] PROGMEM = {
					{'1','2','3','A'},
					{'4','5','6','B'},
					{'7','8','9','C'},
					{'*','0','#','D'}
					};
					
unsigned char read_keyboard()
{
	unsigned char n, j, key=0xFF, line;
	for(n = 0; n < 4; ++n)
	{
		CLR_BIT(COL,n);
		_delay_ms(10);
		
		line = LINE >> 4;

		for(j = 0; j < 4; ++j)
		{
			if(!TST_BIT(line,j))
			{
				key = pgm_read_byte(&kb[j][n]);
				while(!TST_BIT(LINE>>4,j));
			}
		}
		SET_BIT(COL,n);
	}
	return key;
}
