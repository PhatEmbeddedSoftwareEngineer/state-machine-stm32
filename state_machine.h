#ifndef __STATE_MACHINE_H
#define __STATE_MACHINE_H

#include "stm32f10x.h"                  // Device header
#include "stm32f10x_gpio.h"             // Device:StdPeriph Drivers:GPIO
#include "stm32f10x_rcc.h"              // Device:StdPeriph Drivers:RCC
#include "stm32f10x_tim.h"              // Device:StdPeriph Drivers:TIM

enum event
{
	ON,
	OFF
};



typedef enum 
{
	ALL_OFF,
	LED1_OFF,
	LED2_OFF,
	LED3_OFF,
	LED1_LIGHT,
	LED2_LIGHT,
	LED3_LIGHT,
	
}led_state_t;

extern led_state_t curr_state;

typedef struct 
{
	uint16_t led1;
	uint16_t led2;
	uint16_t led3;
}pin_led_config;


void rcc_config();
void gpio_config();
void Timer_Config();
void delay_ms(uint16_t delay);

void led_init(pin_led_config *pin);
void led_practice(uint8_t state,pin_led_config pin);
void led_state_machine(uint8_t event, pin_led_config pin);


#endif