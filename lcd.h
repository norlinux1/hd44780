/*****************************************************************************
-------------------------MicroElectronic-------------------------------------
 basic library for LCD16x2 hd44780 check more http://www.microelectronic.pt
 ---------------------------------------------------------------------------
 This code is distributed under the GNU Public License
 which can be found at http://www.gnu.org/licenses/gpl.txt
*****************************************************************************/
#ifndef LCDLight
#define LCDLight

#include <inttypes.h>
/* Define here hardware configuration of LCD 16x2 */
#define LCD_CONTROL_PORT	PORTD	//define port connected to LCD control pins
#define LCD_CONTROL_DDR		DDRD	//define direction register for port 
/*-----must be the same port------*/
#define LCD_RS	0 	//define LCD RS
#define LCD_RW	1 	//define LCD R/W
#define LCD_E	2	//define LCD E
/*--------------------------------*/
#define LCD_D4	4	//define LCD D3
#define LCD_D5	5	//define LCD D4
#define LCD_D6	6	//define LCD D5
#define LCD_D7	7	//define LCD D6
/*-------------------------------*/
#define SET_E		LCD_CONTROL_PORT|=1<<LCD_E
#define SET_RS		LCD_CONTROL_PORT|=1<<LCD_RS
#define CLEAR_E		LCD_CONTROL_PORT&=~(1<<LCD_E)
#define CLEAR_RS	LCD_CONTROL_PORT&=~(1<<LCD_RS)
#define delay_ms(ms) _delay_ms(ms)
/* instruction register bit positions, see HD44780U data sheet */
#define LCD_CLR               0      /* DB0: clear display                  */
#define LCD_DDRAM             7      /* DB7: set DD RAM address             */
// cursor position to DDRAM mapping
#define LCD_LINE0_DDRAM_ADDRESS		0x00
#define LCD_LINE1_DDRAM_ADDRESS		0x40
#define LCD_LINE2_DDRAM_ADDRESS		0x14
#define LCD_LINE3_DDRAM_ADDRESS		0x54
/* Functions to be used for AVR*/
extern void LCDinit(void);								//Initializes LCD
extern void LCDclr(void);								//Clears LCD
extern void LCDprint(const char*);						// print string on lcd (no auto linefeed)
extern void LCDprintXY(const char*,uint8_t, uint8_t);	// print string on lcd (no auto linefeed), in X,Y Position
extern void LCDGotoXY(uint8_t, uint8_t);				//Cursor to X Y position
extern void LCDStringXY(const uint8_t*, uint8_t, uint8_t);//copies flash string to LCD at x,y

#endif

