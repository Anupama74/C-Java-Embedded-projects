

#include "lpc11xx_gpio.h"
#include <319_Energy_LCD.h>

// Data Lines --> Port2(0 to 7)
// RS --> Port0.2
// Enable --> Port0.3

void LCD_Init( void );
void LCD_Message( char addr, char *data_ptr );
void LCD_Comm( unsigned char comm_data );				// Sending Commands
void LCD_Data( unsigned char disp_data );				// Sending Data
void Delay_Little( void );								// For enable pin
void MSDelay( unsigned int Milli_Sec );					// Delay of 1 milli second


void LCD_Init( void )
{
	LPC_GPIO0->DIR = 0xC;
	LPC_GPIO2->DIR = 0xFF;

	LCD_Comm( 0x38 );								// 2 Lines and 5x7 matrix
	LCD_Comm( 0x0E );								// Display ON, Cursor blinking
	LCD_Comm( 0x01 );								// Clear display Screen
	LCD_Comm( 0x06 );								// Shift cursor right
}



void LCD_Message( char addr, char *data_ptr )
{

	LCD_Comm( addr );
	while( *data_ptr != '\0' )
	{
		LCD_Data( *data_ptr );
		data_ptr++;
		MSDelay(1);								// 0.1 sec delay
	}
}



void LCD_Comm( unsigned char comm_data )			// Sending commands to ALCD
{
	LPC_GPIO2->DATA = comm_data;
	LPC_GPIO0->DATA = 0x0;		// ALCD_RS = 0;
	LPC_GPIO0->DATA = 0x8;	// ALCD_Enable = 1;
	Delay_Little();
	LPC_GPIO0->DATA = 0x0;	// ALCD_Enable = 0;
}


void LCD_Data( unsigned char disp_data )			// Sending data to be displayed
{
	LPC_GPIO2->DATA = disp_data;
	LPC_GPIO0->DATA = 0x4;		// ALCD_RS = 1;
	LPC_GPIO0->DATA = 0xC;	// ALCD_Enable = 1;
	Delay_Little();
	LPC_GPIO0->DATA = 0x0;	// ALCD_Enable = 0;
}


void Delay_Little( void )						// For enable pin
{
	int i=0;

	for(i=0;i<500;i++);
	{
		;
	}
}


void MSDelay( unsigned int Milli_Sec )
{
	 unsigned int x,y;

	for(x=0;x<Milli_Sec;x++)
	{
		for(y=0;y<2000;y++)
		{
			;
		}
	}
}





