/**
  ******************************************************************************
  * @file    main.c
  * @author  Ac6
  * @version V1.0
  * @date    01-December-2013
  * @brief   Default main function.
  ******************************************************************************
*/


#include "stm32f10x.h"
#include "PWM.h"

#define PRESCALER 10000
#define ARR_VALUE 1000
#define DUTY_CYCLE 600
#define MOTOR_PIN 6

custom_libraries::PWM motor(TIM3,custom_libraries::channel1,GPIOA,MOTOR_PIN,PRESCALER,ARR_VALUE);
			

int main(void)
{
	//begin the PWM
	motor.begin();
	motor.set_duty_cycle(DUTY_CYCLE);

	while(1){

	}
}
