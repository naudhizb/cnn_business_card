/* 
 * File:   led_status.h
 * Author: kling
 *
 * Created on 27 September 2020, 17:58
 */

#ifndef LED_STATUS_H
#define	LED_STATUS_H

#include <stdint.h>
#include <stdbool.h>
#include "../config.h"

#ifdef	__cplusplus
extern "C" {
#endif
    
    
#define LED_STATUS_BYTES (LED_COUNT * PWM_BITS) / 8 + 1

/* PWM_BITS bit brightness values for each led*/
extern uint8_t led_status[LED_STATUS_BYTES];

void clear_led_brightness();

uint8_t get_led_brightness(uint8_t row, uint8_t col);

bool get_led_on(uint8_t row, uint8_t col);

void set_led_brightness(uint8_t row, uint8_t col, uint8_t val);

uint8_t value_to_pwm_level(float value, float max_value);

void set_filter_leds(uint8_t filter_idx);

void init_pwm_data();

void update_pwm_pattern();

void turn_off_leds();

void run_pwm_cycle();


#ifdef	__cplusplus
}
#endif

#endif	/* LED_STATUS_H */

