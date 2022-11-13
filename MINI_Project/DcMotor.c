 /******************************************************************************
 *
 * Module: DC_Motor
 *
 * File Name: DC_Motor.c
 *
 * Description: Source file for the DC Motor driver
 *
 * Author: Tarek Ahmed
 *
 *******************************************************************************/
#include "DcMotor.h"
#include <avr/io.h>


/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

/*
 * Description :
 * Function responsible for Enable DC Motor.
 */

void DcMotor_Init(void)
{
	/*
	 * Set The DC motor pins an output pins
	 */
	GPIO_setupPinDirection(DC_MotorPort_ID, DC_MotorIN1_Pin_ID, PIN_OUTPUT);
	GPIO_setupPinDirection(DC_MotorPort_ID, DC_MotorIN2_Pin_ID, PIN_OUTPUT);

	/*
	 * Set initial value zero for The Dc motor
	 */
	GPIO_writePin(DC_MotorPort_ID, DC_MotorIN1_Pin_ID, LOGIC_LOW);
	GPIO_writePin(DC_MotorPort_ID, DC_MotorIN2_Pin_ID, LOGIC_LOW);
}


/*
 * Description :
 * Function responsible for set DC motor movement and speed
 */

void DcMotor_Rotate(DcMotor_State state , uint8 speed)
{
	/*
	 * Choose DC motor movement
	 */
	if(state==CW)
	{
		GPIO_writePin(DC_MotorPort_ID, DC_MotorIN1_Pin_ID, LOGIC_HIGH);
		GPIO_writePin(DC_MotorPort_ID, DC_MotorIN2_Pin_ID, LOGIC_LOW);
	}
	else if(state==A_CW)
	{
		GPIO_writePin(DC_MotorPort_ID, DC_MotorIN1_Pin_ID, LOGIC_LOW);
		GPIO_writePin(DC_MotorPort_ID, DC_MotorIN2_Pin_ID, LOGIC_HIGH);
	}
	else if(state==STOP)
	{
		GPIO_writePin(DC_MotorPort_ID, DC_MotorIN1_Pin_ID, LOGIC_LOW);
		GPIO_writePin(DC_MotorPort_ID, DC_MotorIN2_Pin_ID, LOGIC_LOW);
	}

	/*
	 * Choose DC motor speed
	 */
	PWM_Timer0_Start(speed);
}


/*
 * Description :
 * Function responsible for set DC Motor speed
 */

void PWM_Timer0_Start(uint8 duty_cycle)
{
	GPIO_setupPinDirection(PORTB_ID, PIN3_ID, PIN_OUTPUT);
	TCNT0=0;
	OCR0=((uint16)(duty_cycle*255))/100;/*Choose  DC motor Speed*/

	TCCR0 = (1<<WGM00) | (1<<WGM01)   /*Choose  FAST PWM */
			| (1<<COM01)              /*Choose  Non_Inverting */
			| (1<<CS01);              /*Choose Prescaler F_CPU_8 */
}

