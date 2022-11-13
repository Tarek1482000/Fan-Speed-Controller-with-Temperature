 /******************************************************************************
 *
 * Module: ADC
 *
 * File Name: adc.c
 *
 * Description: Source file for the ATmega32 ADC driver
 *
 * Author: Tarek Ahmed
 *
 *******************************************************************************/

#include "avr/io.h" /* To use the ADC Registers */
#include "adc.h"  /* To use the ADC Definitions */
#include "common_macros.h" /* To use the macros like SET_BIT */

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

void ADC_init(const ADC_ConfigType *Config_Ptr)
{
	/* ADMUX Register Bits Description:
	 * REFS1:0 = To choose reference voltage by input this voltage through AREF pin
	 * ADLAR   = 0 right adjusted
	 * MUX4:0  = 00000 to choose channel 0 as initialization
	 */
	ADMUX = (ADMUX & 0X00) | ((Config_Ptr->ref_volt)<<6);

	/* ADCSRA Register Bits Description:
	 * ADEN    = 1 Enable ADC
	 * ADIE    = 0 Disable ADC Interrupt
	 * ADATE   = 0 Disable Auto Trigger
	 * ADPS2:0 = TO choose ADC_Clock = F_CPU/8 = 1Mhz/8
	 */
	ADCSRA = (1<<ADEN) ;

	ADCSRA = (ADCSRA & 0xF8) | (Config_Ptr->prescaler);
}

uint16 ADC_readChannel(uint8 channel_num)
{
	 /* Input channel number must be from 0 --> 7 */
	 /* Clear first 5 bits in the ADMUX (channel number MUX4:0 bits) before set the required channel */
	/* Choose the correct channel by setting the channel number in MUX4:0 bits */
	ADMUX = (ADMUX & 0xE0) | (channel_num & 0x07) ;
	SET_BIT(ADCSRA,ADSC); /* Start conversion write '1' to ADSC */
	while(BIT_IS_CLEAR(ADCSRA,ADIF)); /* Wait for conversion to complete, ADIF becomes '1' */
	SET_BIT(ADCSRA,ADIF); /* Clear ADIF by write '1' to it :) */
	return ADC; /* Read the digital value from the data register */
}
