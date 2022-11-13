 /******************************************************************************
 *
 * Module: ADC
 *
 * File Name: adc.h
 *
 * Description: header file for the ATmega32 ADC driver
 *
 * Author: Tarek Ahmed

 *******************************************************************************/

#ifndef ADC_H_
#define ADC_H_

#include "std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define ADC_MAXIMUM_VALUE    1023



typedef enum
{
	AREF,AVCC,REVERSED,INTERNAL
}ADC_ReferenceVoltage;


typedef enum
{
	F_CPU_2=1 , F_CPU_4=2 , F_CPU_8=3 , F_CPU_16=4 , F_CPU_32=5 , F_CPU_64=6 , F_CPU_128=7
}ADC_Prescaler;


/* To choose the ADC Reference Volt and prescaler */
typedef struct
{
	ADC_ReferenceVoltage ref_volt;
	ADC_Prescaler prescaler;

}ADC_ConfigType;


/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Function responsible for initialize the ADC driver.
 */
void ADC_init(const ADC_ConfigType *Config_Ptr);

/*
 * Description :
 * Function responsible for read analog data from a certain ADC channel
 * and convert it to digital using the ADC driver.
 */
uint16 ADC_readChannel(uint8 channel_num);



/*
 * Description :
 * Function responsible for return reference voltage to use in other modules
 */
uint8 ADC_refVolt(uint8 *adc_ref_volt);
#endif /* ADC_H_ */
