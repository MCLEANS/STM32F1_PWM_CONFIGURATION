/*
 * PWM.cpp
 *
 *  Created on: Apr 1, 2020
 *      Author: MCLEANS
 */

#include "PWM.h"

namespace custom_libraries {

PWM::PWM(TIM_TypeDef *TIMER,
		channel input_channel,
		GPIO_TypeDef *PORT,
		uint8_t PIN,
		uint16_t prescaler,
		uint16_t auto_reload_value ):TIMER(TIMER),
									input_channel(input_channel),
									PORT(PORT),
									PIN(PIN),
									prescaler(prescaler),
									auto_reload_value(auto_reload_value)
										{
	//Enable Timer RCC
	if(TIMER == TIM1) RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
	if(TIMER == TIM2) RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
	if(TIMER == TIM3) RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
	if(TIMER == TIM4) RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;

	//Enable GPIO RCC
	if(PORT == GPIOA) RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
	if(PORT == GPIOB) RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
	if(PORT == GPIOC) RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
	if(PORT == GPIOD) RCC->APB2ENR |= RCC_APB2ENR_IOPDEN;
	if(PORT == GPIOE) RCC->APB2ENR |= RCC_APB2ENR_IOPEEN;


	//Set pin to alternate function mode
	if(PIN < 8){
			PORT->CRL |= (1<<(PIN*4))|(1<<((PIN*4)+1))|(1<<((PIN*4)+3));
			PORT->CRL &= ~(1<<((PIN*4)+2));
		}
		else{
			PIN = PIN-8;
			PORT->CRH |= (1<<(PIN*4))|(1<<((PIN*4)+1))|(1<<((PIN*4)+3));
			PORT->CRH &= ~(1<<((PIN*4)+2));
		}

	TIMER->PSC = this->prescaler;
	TIMER->ARR = this-> auto_reload_value;


}

void PWM::set_prescaler(uint16_t prescaler){

	if(prescaler != this->prescaler){
		this->prescaler = prescaler;
		TIMER->PSC = this->prescaler;
	}


}

uint16_t PWM::get_prescaler(void)const{
	return this->prescaler;

}

void PWM::set_auto_reload_value(uint16_t auto_reload_value){

	if(auto_reload_value != this->auto_reload_value) {
		this->auto_reload_value = auto_reload_value;
		TIMER->ARR = this->auto_reload_value;
	}


}

uint16_t PWM::get_auto_reload_value(void) const{
	return this->auto_reload_value;
}

void PWM::set_duty_cycle(uint16_t duty_cycle){

	if(duty_cycle != this->duty_cycle){
		this->duty_cycle = duty_cycle;

		if(input_channel == channel1) TIMER->CCR1 = this->duty_cycle;
		if(input_channel == channel2) TIMER->CCR2 = this->duty_cycle;
		if(input_channel == channel3) TIMER->CCR3 = this->duty_cycle;
		if(input_channel == channel4) TIMER->CCR4 = this->duty_cycle;
	}

}

uint16_t PWM::get_duty_cycle(void) const{
	return this->duty_cycle;
}



void PWM::begin(){
	//set to PWM Mode 1
	if(input_channel == channel1){
		TIMER->CCMR1 &= ~(TIM_CCMR1_OC1M_0);
		TIMER->CCMR1 |= TIM_CCMR1_OC1M_1;
		TIMER->CCMR1 |= TIM_CCMR1_OC1M_2;
		//Set output compare preload enable
		TIMER->CCMR1 |= TIM_CCMR1_OC1PE;
		//Enable capture/compare output
		TIMER->CCER |= TIM_CCER_CC1E;
	}

	if(input_channel == channel2){
		TIMER->CCMR1 &= ~(TIM_CCMR1_OC2M_0);
		TIMER->CCMR1 |= TIM_CCMR1_OC2M_1;
		TIMER->CCMR1 |= TIM_CCMR1_OC2M_2;
		//Set output compare preload enable
		TIMER->CCMR1 |= TIM_CCMR1_OC2PE;
		//Enable capture/compare output
		TIMER->CCER |= TIM_CCER_CC2E;
	}

	if(input_channel == channel3){
		TIMER->CCMR2 &= ~(TIM_CCMR2_OC3M_0);
		TIMER->CCMR2 |= TIM_CCMR2_OC3M_1;
		TIMER->CCMR2 |= TIM_CCMR2_OC3M_2;
		//Set output compare preload enable
		TIMER->CCMR2 |= TIM_CCMR2_OC3PE;
		//Enable capture/compare output
		TIMER->CCER |= TIM_CCER_CC3E;
	}

	if(input_channel == channel4){
		TIMER->CCMR2 &= ~(TIM_CCMR2_OC4M_0);
		TIMER->CCMR2 |= TIM_CCMR2_OC4M_1;
		TIMER->CCMR2 |= TIM_CCMR2_OC4M_2;
		//Set output compare preload enable
		TIMER->CCMR2 |= TIM_CCMR2_OC4PE;
		//Enable capture/compare output
		TIMER->CCER |= TIM_CCER_CC4E;
	}

	//set main Output Enable
	TIMER->BDTR |= TIM_BDTR_MOE;
	//Enable the UG bit to update preload register
	TIMER->EGR |= TIM_EGR_UG;
	//Enable timer
	TIMER->CR1 |= TIM_CR1_CEN;

}


PWM::~PWM() {
	// TODO Auto-generated destructor stub
}

} /* namespace custom_libraries */
