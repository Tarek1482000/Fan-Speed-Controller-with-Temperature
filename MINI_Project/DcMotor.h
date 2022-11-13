 /******************************************************************************
 *
 * Module: Dc Motor
 *
 * File Name: DcMotor.h
 *
 * Author: Tarek Ahmed
 *
 *******************************************************************************/

#ifndef DCMOTOR_H_
#define DCMOTOR_H_

#include "std_types.h"
#include "gpio.h"
/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

#define DC_MotorPort_ID       PORTB_ID
#define DC_MotorIN1_Pin_ID    PIN0_ID
#define DC_MotorIN2_Pin_ID    PIN1_ID

typedef enum
{
	CW , A_CW ,STOP
}DcMotor_State;


/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

void DcMotor_Init(void);

void DcMotor_Rotate(DcMotor_State state , uint8 speed);


void PWM_Timer0_Start(uint8 duty_cycle);


#endif /* DCMOTOR_H_ */
