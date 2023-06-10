#include "sleep.h"
#include "../config.h"
#include "led_control.h"

#include <stdint.h>
#include "cmsis_compiler.h"
#include "stm32f4xx_hal.h"


void _delay_us(uint32_t us)
{
    uint32_t us_tick =  SystemCoreClock/1000000;
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

void go_to_sleep() {
    /* Go to sleep, wakeup on PWR button press
     * unfortunately synchronous pins like PB3 can only wake the chip
     * with BOTHEDGES or LEVEL interrupts, so we have to wait until the
     * button is released (and no longer bouncing) before going to sleep.
     */
//    _delay_ms(50);
//    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
//    sleep_enable();
//    sleep_cpu();
//    turn_off_leds();
    // turn off individual leds
//    _delay_ms(50);
//    reset_rtc_cnt();
}
