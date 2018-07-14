



void LCD_Init( void );
void LCD_Message( char addr, char *data_ptr );
void LCD_Comm( unsigned char comm_data );				// Sending Commands
void LCD_Data( unsigned char disp_data );				// Sending Data
void Delay_Little( void );								// For enable pin
void MSDelay( unsigned int Milli_Sec );					// Delay of 1 milli second

