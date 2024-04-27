#include "state_machine.h"

led_state_t curr_state;
void led_state_machine(uint8_t event, pin_led_config pin)
{
	while(1)
	{
	led_state_t prev_state;
	prev_state=curr_state;
	switch (curr_state)
	{
		case ALL_OFF:
		{
			switch(event)
			{
				
				case ON:
				{
					curr_state = LED1_LIGHT;
					//*state=0;
					break;
				}
				case OFF:
				{
					curr_state=ALL_OFF;
					break;
				}
			}
			break;
		}
		case LED1_LIGHT:
		{
			curr_state=LED2_LIGHT;
			//*state=0;
			break;
		}
		case LED1_OFF:
		{
			curr_state=LED2_OFF;
			//*state=0;
			break;
		}
		
		case LED2_LIGHT:
		{
			curr_state=LED3_LIGHT;
			//*state=0;
			break;
			
		}
		case LED2_OFF:
		{
			curr_state=LED3_OFF;
			//*state=0;
			break;
			
		}
		
		case LED3_LIGHT:
		{
			curr_state=LED1_OFF;
			//*state=0;
			break;
		}
		case LED3_OFF:
		{
			curr_state=LED1_LIGHT;
			//*state=1;
			goto exit;
			break;
		}
	}
	if(prev_state != curr_state)
	{
		led_practice(curr_state,pin);
	}
}
	exit:;
}
void led_init(pin_led_config *pin)
{
	
	
	pin->led1=GPIO_Pin_0;
	pin->led2=GPIO_Pin_1;
	pin->led3=GPIO_Pin_2;
	//led_practice(curr_state,pin->led1|pin->led2|pin->led3);
	
}



void led_practice(uint8_t state,pin_led_config pin)
{
	switch (state)
	{
		case ALL_OFF:
		{
			GPIO_ResetBits(GPIOA,pin.led1 | pin.led2 | pin.led3);
			delay_ms(100);
			break;
		}
		
		case LED1_OFF:
		{
			GPIO_ResetBits(GPIOA,pin.led1);
			delay_ms(100);
			break;
			
		}
		case LED2_OFF:
		{
			GPIO_ResetBits(GPIOA,pin.led2);
			delay_ms(100);
			break;
		}
		
		case LED3_OFF:
		{
			GPIO_ResetBits(GPIOA,pin.led3);
			delay_ms(100);
			break;
		}
		
		case LED1_LIGHT:
		{
			GPIO_SetBits(GPIOA,pin.led1);
			delay_ms(100);
			break;
		}
		case LED2_LIGHT:
		{
			GPIO_SetBits(GPIOA,pin.led2);
			delay_ms(100);
			break;
		}
		case LED3_LIGHT:
		{
			GPIO_SetBits(GPIOA,pin.led3);
			delay_ms(100);
			break;
		}
	}
}


void delay_ms(uint16_t delay)
{
	TIM_SetCounter(TIM2,0);
	while(TIM_GetCounter(TIM2)<delay*10);
}


void gpio_config()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOC,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	
}
void rcc_config()
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE); // 36mhz
}
void Timer_Config()
{
	TIM_TimeBaseInitTypeDef TIM_InitStructure;
	
	// KET QUA VAN LA 36MHZ
	
	TIM_InitStructure.TIM_ClockDivision=TIM_CKD_DIV1;
	/*
		trong 1s no xu ly 36 trieu dao dong
		0.1ms dem len 1 lan 
		gia tri bat dau tu 0
	*/
	TIM_InitStructure.TIM_Prescaler=7200-1;
	
	/*
	cho dem thoai mai
	*/
	TIM_InitStructure.TIM_Period=65536-1;
	/*
		dem len tu 0
	*/
	TIM_InitStructure.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM2,&TIM_InitStructure);
	TIM_Cmd(TIM2,ENABLE);
	
}
