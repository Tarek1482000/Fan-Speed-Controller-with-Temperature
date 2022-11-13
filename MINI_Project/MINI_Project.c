/******************************************************************************
 *
 * Module: main function
 *
 * File Name: MINI_Project.c
 *
 * Author: Tarek Ahmed
 *
 *******************************************************************************/


#include <avr/io.h>
#include "lcd.h"
#include "adc.h"
#include "std_types.h"
#include "lm35_sensor.h"
#include "DcMotor.h"

void main(void)
{
	uint8 Lm35_result=0;

	ADC_ConfigType Config_Ptr={INTERNAL , F_CPU_8}; /* Set ADC Driver Voltage and Prescaler */

	LCD_init(); /* Turn on LCD */
	DcMotor_Init(); /* Turn on DC Motor */
	ADC_init(&Config_Ptr); /* Turn on ADC */

	SREG |= (1<<7);/* Set I-bit */

	LCD_displayStringRowColumn(0, 3, "FAN is ");
	LCD_displayStringRowColumn(1, 3, "Temp =    C");

	for(;;)
	{
		Lm35_result=LM35_getTemperature(); /* Get Sensor Value */

		if(Lm35_result<30)
		{
			LCD_displayStringRowColumn(0, 10, "OFF"); /* Display Turn OFF FAN on LCD */
			DcMotor_Rotate(STOP, 0); /* Turn OFF FAN and set speed 0% */
		}


		else if((Lm35_result>=30) && (Lm35_result<60))
		{
			LCD_displayStringRowColumn(0, 10, "ON ");/* Display Turn ON FAN on LCD */
			DcMotor_Rotate(CW, 25); /* Turn ON FAN in clock wise direction and set speed 25% */
		}


		else if((Lm35_result>=60) && (Lm35_result<90))
		{
			LCD_displayStringRowColumn(0, 10, "ON "); /* Display Turn ON FAN on LCD */
			DcMotor_Rotate(CW, 50);/* Turn ON FAN in clock wise direction and set speed 50% */
		}


		else if((Lm35_result>=90) && (Lm35_result<120))
		{
			LCD_displayStringRowColumn(0, 10, "ON "); /* Display Turn ON FAN on LCD */
			DcMotor_Rotate(CW, 75);/* Turn ON FAN in clock wise direction and set speed 75% */
		}


		else if(Lm35_result>=120)
		{
			LCD_displayStringRowColumn(0, 10, "ON "); /* Display Turn ON FAN on LCD */
			DcMotor_Rotate(CW, 100);/* Turn ON FAN in clock wise direction and set speed 100% */
		}



		/*
		 * Display Sensor value On LCD
		 */
		LCD_moveCursor(1,10);
		if(Lm35_result>=100)
		{
			LCD_intgerToString(Lm35_result);
		}
		else
		{
			LCD_intgerToString(Lm35_result);
			LCD_displayCharacter(' ');
		}

	}

}
