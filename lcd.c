/*****************************************************************************
-------------------------MicroElectronic-------------------------------------
 basic library for LCD16x2 hd44780 check more http://www.microelectronic.pt
 ---------------------------------------------------------------------------
 This code is distributed under the GNU Public License
 which can be found at http://www.gnu.org/licenses/gpl.txt
*****************************************************************************/
#include "lcd.h"
#include <inttypes.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#ifndef F_CPU
#define F_CPU 8000000UL
#endif
#include <util/delay.h>


void LCDcommand(uint8_t cmd)	//Sends Command to LCD
{
	LCD_CONTROL_PORT=(cmd&0b11110000);
	SET_E;		
	delay_ms(1);
	CLEAR_E;
	delay_ms(1);
	LCD_CONTROL_PORT=((cmd&0b00001111)<<4);	
	SET_E;		
	delay_ms(1);
	CLEAR_E;
	delay_ms(1);
}
void LCDinit(void)//Initializes LCD
{
	delay_ms(15);
	LCD_CONTROL_DDR|=1<<LCD_D7|1<<LCD_D6|1<<LCD_D5|1<<LCD_D4|1<<LCD_E|1<<LCD_RW|1<<LCD_RS;
	LCD_CONTROL_PORT=0x00;
   //---------one------
	LCD_CONTROL_PORT|=0<<LCD_D7|0<<LCD_D6|1<<LCD_D5|1<<LCD_D4|1<<LCD_E|0<<LCD_RW|0<<LCD_RS;	
	delay_ms(1);
	CLEAR_E;
	delay_ms(1);
	//-----------two-----------
	LCD_CONTROL_PORT|=0<<LCD_D7|0<<LCD_D6|1<<LCD_D5|1<<LCD_D4|1<<LCD_E|0<<LCD_RW|0<<LCD_RS; 
	delay_ms(1);
	CLEAR_E;
	delay_ms(1);
	//-------three-------------
	LCD_CONTROL_PORT=0<<LCD_D7|0<<LCD_D6|1<<LCD_D5|0<<LCD_D4|1<<LCD_E|0<<LCD_RW|0<<LCD_RS; 
	delay_ms(1);
	CLEAR_E;
	delay_ms(1);
	//--------4 bit--dual line---------------
	LCDcommand(0b00101000);
   //-----increment address, invisible cursor shift------
	LCDcommand(0b00001100);
}			
void LCDclr(void)				//Clears LCD
{
	LCDcommand(1<<LCD_CLR);
}


void LCDGotoXY(uint8_t x, uint8_t y)	//Cursor to X Y position
{
	register uint8_t DDRAM_ADDRESS;
	switch(y)
	{
	case 0: DDRAM_ADDRESS = LCD_LINE0_DDRAM_ADDRESS+x; break;
	case 1: DDRAM_ADDRESS = LCD_LINE1_DDRAM_ADDRESS+x; break;
	case 2: DDRAM_ADDRESS = LCD_LINE2_DDRAM_ADDRESS+x; break;
	case 3: DDRAM_ADDRESS = LCD_LINE3_DDRAM_ADDRESS+x; break;
	default: DDRAM_ADDRESS = LCD_LINE0_DDRAM_ADDRESS+x;
	}
	// set data address
	LCDcommand(1<<LCD_DDRAM | DDRAM_ADDRESS);
	
}

void LCDsendChar(uint8_t ch)		//Sends Char to LCD
{

	LCD_CONTROL_PORT=(ch&0b11110000);
	SET_RS;
	SET_E;
	delay_ms(1);
	CLEAR_E;
	CLEAR_RS;
	delay_ms(1);
	LCD_CONTROL_PORT=((ch&0b00001111)<<4);
	SET_RS;
	SET_E;
	delay_ms(1);
	CLEAR_E;
	CLEAR_RS;
	delay_ms(1);
}
//Copies string from flash memory to LCD at x y position
void LCDStringXY(const uint8_t *Flash, uint8_t x, uint8_t y)
{
	uint8_t i;
	LCDGotoXY(x,y);
	for(i=0;(uint8_t)pgm_read_byte(&Flash[i]);i++)
	{
		LCDsendChar((uint8_t)pgm_read_byte(&Flash[i]));
	}
}
/*Display string without auto linefeed */
void LCDprint(const char *s)
/* print string on lcd (no auto linefeed) */
{
	register char c;
	while ( (c = *s++) )
		LCDsendChar(c);
}