#include "sleep.h"
#include "../config.h"
#include "led_control.h"

#include <stdint.h>
#include "cmsis_compiler.h"
#include "stm32f4xx_hal.h"


void _delay_us(uint32_t us)
{
    uint32_t us_tick =  SystemCoreClock/1000000/3;
	for(volatile int i = 0; i < us; i++)
	{
		for(volatile int j = 0; j < us_tick; j++)
		{
		}
	}
}

void _delay_ms(uint32_t ms)
{
	HAL_Delay(ms);
}

static int LastUpdate = 0;
void reset_rtc_cnt() {
    /* reset RTC (auto shutdown counter) */
    LastUpdate = HAL_GetTick();
}
int check_rtc_elapsed()
{
    return (HAL_GetTick() - LastUpdate) > 1000*60*5;
}

void go_to_sleep() {
    /* Go to sleep, wakeup on PWR button press
     * unfortunately synchronous pins like PB3 can only wake the chip
     * with BOTHEDGES or LEVEL interrupts, so we have to wait until the
     * button is released (and no longer bouncing) before going to sleep.
     */
    extern TIM_HandleTypeDef htim5;
    extern TIM_HandleTypeDef htim11;
    // turn off individual leds
   turn_off_leds();
   //_delay_ms(50);
   HAL_TIM_Base_Stop_IT(&htim11);
   HAL_TIM_Base_Stop_IT(&htim5);
   HAL_PWR_EnterSLEEPMode(PWR_MAINREGULATOR_ON, PWR_SLEEPENTRY_WFI);
   HAL_TIM_Base_Start_IT(&htim11);
   HAL_TIM_Base_Start_IT(&htim5);
   //_delay_ms(50);
   reset_rtc_cnt();
}
