

//--------------------------------------------------------------------------------------------------------------------
// Includes
//--------------------------------------------------------------------------------------------------------------------

#include "lpc11xx_adc.h"
#include "LPC11xx.h"
#include "lpc11xx_gpio.h"
#include "lpc11xx_syscon.h"
#include "lpc11xx_libcfg.h"
#include "319_Energy_LCD.h"
#include "319_Energy_UART.h"


//--------------------------------------------------------------------------------------------------------------------
// Global VARIABLES
//--------------------------------------------------------------------------------------------------------------------

//unsigned char Disp_Line1[8] = "S= 00.0";

unsigned char Disp_Line1[17] = "S= 00.0  L= 00.0";
unsigned char Disp_Line2[17] = "B= 00.0  A= 00.0";

//unsigned char Disp_Line2[17] = "BATT VOLT = 00.0";

extern volatile uint8_t UARTBuffer[BUFSIZE];
extern volatile uint32_t UARTCount;
extern char Rx_St_flag;

extern FlagStatus bitSta;

extern unsigned char Voltage_Arr[6];
extern unsigned int Volt_Temp;

 //--------------------------------------------------------------------------------------------------------------------
// Function PROTOTYPES
//--------------------------------------------------------------------------------------------------------------------

void Device_Init( void );


//--------------------------------------------------------------------------------------------------------------------
// void main (void)
//--------------------------------------------------------------------------------------------------------------------

int main(void)
{
// P2.0-7 for LCD Data Lines
// P0.2 for LCD RS
// P0.3 for LCD Enable

// P3.2 --> Buzz output
// P3.3 --> LED output
// ZIGBEE UART0 through MUX4052 --> P1.6, P1.7
// P2.8 --> Repair_Key input
// P2.9 --> Emergency_Key input
// P2.10 --> Help_Key input
// P2.11 --> LDR Sensor input

	unsigned char i;


	Device_Init( );
	MSDelay(500);


	GPIO_SetBits(PORT3, GPIO_Pin_0);			// Batt Relay output
	MSDelay(2000);
	GPIO_ResetBits(PORT3, GPIO_Pin_0);			// Batt Relay output
	MSDelay(1000);


	GPIO_ResetBits(PORT3, GPIO_Pin_1);			// Bulb Relay output
	MSDelay(2000);
	GPIO_SetBits(PORT3, GPIO_Pin_1);			// Bulb Relay output
	MSDelay(1000);


	LCD_Comm( 0x01 );								// Clear display Screen
	MSDelay(300);
	LPC_UART->IER = IER_THRE | IER_RLS | IER_RBR;	// Re-enable RBR
	UARTCount = 0;									// Take UART Receiver array to zeroth location
	Rx_St_flag = 0;

	LCD_Message( 0x80, Disp_Line1 );
	MSDelay(300);
	while(1)
	{
		ADC_START(1);
		LCD_Message( 0x83, Voltage_Arr );
		if( (Voltage_Arr[0] == '0') && (Voltage_Arr[1] <= '7') )
		{
			GPIO_SetBits(PORT3, GPIO_Pin_0);			// Batt Relay output
			MSDelay(2000);
		}
		else
		{
			GPIO_ResetBits(PORT3, GPIO_Pin_0);			// Batt Relay output
			MSDelay(2000);
		}


		ADC_START(2);
		LCD_Message( 0x8C, Voltage_Arr );
		if( Volt_Temp >= 400 )
		{
			GPIO_ResetBits(PORT3, GPIO_Pin_1);			// Bulb Relay output
			LCD_Message( 0xC0, "OVERLOAD DETECT " );
			UARTSend( "OV@", 3 );

			MSDelay(4000);
			LCD_Message( 0xC0, "                " );
			UARTCount = 0;								// Take UART Receiver array to zeroth location
			Rx_St_flag = 0;
		}
		MSDelay(2000);



		if( Rx_St_flag == 1 )
		{
			LCD_Message( 0xC0, " DATA RECEIVED  " );
			MSDelay(1000);
			if( (UARTBuffer[0]=='B') && (UARTBuffer[1]=='1') )
			{
				GPIO_SetBits(PORT3, GPIO_Pin_1);			// Bulb Relay output
				LCD_Message( 0xC0, "    BULB ON    " );
			}
			else if( (UARTBuffer[0]=='B') && (UARTBuffer[1]=='0') )
			{
				GPIO_ResetBits(PORT3, GPIO_Pin_1);			// Bulb Relay output
				LCD_Message( 0xC0, "    BULB OFF   " );
			}

			MSDelay(4000);
			LCD_Message( 0xC0, "                " );
			UARTCount = 0;								// Take UART Receiver array to zeroth location
			Rx_St_flag = 0;
		}

	}



    while(1)
    {
    }
}



void Device_Init( void )
{
    LPC_SYSCON->SYSAHBCLKCTRL |= SYSCON_AHBPeriph_GPIO & SYSCON_AHBPeriph_BITMASK;

    SystemInit();
    SYSCON_AHBPeriphClockCmd(SYSCON_AHBPeriph_GPIO, ENABLE);


	MSDelay(100);
	LCD_Init( );
	MSDelay(100);
	LCD_Message( 0x80, "  SMART ENERGY  " );
	LCD_Message( 0xC0, "   MANAGEMENT   " );


    GPIO_SetDir(PORT3, GPIO_Pin_0, 1);			// Batt Relay output output
    GPIO_SetDir(PORT3, GPIO_Pin_1, 1);			// Bulb Relay output output


	MSDelay(200);
    GPIO_ResetBits(PORT3, GPIO_Pin_0);			// Batt Relay output output
	GPIO_ResetBits(PORT3, GPIO_Pin_1);			// LED output output


    UARTInit(9600);
	UARTSend( "UART BT@", 8 );
	MSDelay(500);
}












