#include "state_machine.h"


int main(void)
{
	rcc_config();
	gpio_config();
	Timer_Config();
	pin_led_config led;
	led_init(&led);
	curr_state = ALL_OFF;
	led_practice(curr_state,led);
	
	/*
		run state machine 
	*/
	
	led_state_machine(ON,led);

	return 0;
}

