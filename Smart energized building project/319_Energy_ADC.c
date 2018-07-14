#include "lpc11xx_adc.h"


unsigned int adc_value_temp,adc_value_temp1,adc_value_temp2,adc_value1,Volt_Temp;
unsigned char Voltage_Arr[6] = "00.00";

void ADC_START(unsigned int n)
{
	uint32_t adc_value;
	char buf[6];
	/* Configuration for ADC :
	 * 	Frequency at 1Mhz
	 *  ADC channel 2, no Interrupt
	 *
	 *	ADC Pins:
	 *	AD0 - P0.11
	 *	AD1 - P1.0
	 *	AD2 - P1.1
	 *	AD3 - P1.2
	 *	AD4 - P1.3
	 *	AD5 - P1.4
	 *	AD6 - P1.10
	 *	AD7 - P1.11
	 */

    switch(n)
    {
		case 1 :
		{
			ADC_Init(1000000);
			ADC_IntConfig(ADC_ADINTEN1,ENABLE);
			ADC_PinsInit(ADC_CHANNEL_1);
			ADC_ChannelCmd(ADC_CHANNEL_1,ENABLE);

			/* Start conversion */
			ADC_StartCmd(ADC_START_NOW);
			/* Wait conversion complete */
			while (!(ADC_ChannelGetStatus(ADC_CHANNEL_1,ADC_DATA_DONE)));
			adc_value = ADC_ChannelGetData(ADC_CHANNEL_1);

		   break;
		}

		case 2 :
		{
			ADC_Init(1000000);
			ADC_IntConfig(ADC_ADINTEN2,ENABLE);
			ADC_PinsInit(ADC_CHANNEL_2);
			ADC_ChannelCmd(ADC_CHANNEL_2,ENABLE);

			/* Start conversion */
			ADC_StartCmd(ADC_START_NOW);
			/* Wait conversion complete */
			while (!(ADC_ChannelGetStatus(ADC_CHANNEL_2,ADC_DATA_DONE)));
			adc_value = ADC_ChannelGetData(ADC_CHANNEL_2);

		   break;
		}

		case 3 :
		{
			ADC_Init(1000000);
			ADC_IntConfig(ADC_ADINTEN3,ENABLE);
			ADC_PinsInit(ADC_CHANNEL_3);
			ADC_ChannelCmd(ADC_CHANNEL_3,ENABLE);

		    /* Start conversion */
			ADC_StartCmd(ADC_START_NOW);
			/* Wait conversion complete */
			while (!(ADC_ChannelGetStatus(ADC_CHANNEL_3,ADC_DATA_DONE)));
			adc_value = ADC_ChannelGetData(ADC_CHANNEL_3);

		   break;
		}

		case 4 :
		{
			ADC_Init(1000000);
			ADC_IntConfig(ADC_ADINTEN4,ENABLE);
			ADC_PinsInit(ADC_CHANNEL_4);
			ADC_ChannelCmd(ADC_CHANNEL_4,ENABLE);

			/* Start conversion */
			ADC_StartCmd(ADC_START_NOW);
			/* Wait conversion complete */
			while (!(ADC_ChannelGetStatus(ADC_CHANNEL_4,ADC_DATA_DONE)));
			adc_value = ADC_ChannelGetData(ADC_CHANNEL_4);

			break;
		}

		case 5 :
		{
			ADC_Init(1000000);
			ADC_IntConfig(ADC_ADINTEN5,ENABLE);
			ADC_PinsInit(ADC_CHANNEL_5);
			ADC_ChannelCmd(ADC_CHANNEL_5,ENABLE);

			/* Start conversion */
			ADC_StartCmd(ADC_START_NOW);
			/* Wait conversion complete */
			while (!(ADC_ChannelGetStatus(ADC_CHANNEL_5,ADC_DATA_DONE)));
			adc_value = ADC_ChannelGetData(ADC_CHANNEL_5);

		   break;
		}
	}


	adc_value_temp = ((adc_value*3.0)/1023)*100;

/*
	adc_value_temp1 = adc_value_temp;
	Volt_Temp = adc_value_temp;

	Voltage_Arr[4] =  (adc_value_temp1%10)+48;
	adc_value_temp1 = adc_value_temp1/10;
	Voltage_Arr[3] =  (adc_value_temp1%10)+48;
	adc_value_temp1 = adc_value_temp1/10;
	Voltage_Arr[1] =  (adc_value_temp1%10)+48;
	adc_value_temp1 = adc_value_temp1/10;
	Voltage_Arr[0] =  (adc_value_temp1%10)+48;
*/

	adc_value_temp1 = adc_value_temp * 10;
	Volt_Temp = adc_value_temp1;

	Voltage_Arr[4] =  (adc_value_temp1%10)+48;
	adc_value_temp1 = adc_value_temp1/10;
	Voltage_Arr[3] =  (adc_value_temp1%10)+48;
	adc_value_temp1 = adc_value_temp1/10;
	Voltage_Arr[1] =  (adc_value_temp1%10)+48;
	adc_value_temp1 = adc_value_temp1/10;
	Voltage_Arr[0] =  (adc_value_temp1%10)+48;

	Voltage_Arr[4] =  '\0';
}
