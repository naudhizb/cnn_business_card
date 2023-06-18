#include "led_control.h"
#include "../config.h"

#include <stdint.h>
#include <stdbool.h>
#include "sleep.h"

#include "../led_matrix.h"

/* PWM_BITS-bit brightness values for each led*/
uint8_t led_status[LED_STATUS_BYTES] = {0};


/* precomputed bytes to shift out during main loop*/
uint16_t row_shift_bytes[9];
uint16_t col_shift_bytes[PWM_LEVELS * 9];

/* brightness of row8 leds (not controlled via shift register) */
uint16_t row8_brightness[9];


/* gamma correction table
 * led_value ∈ [0,1)= (perceived brightness ∈ [0,1))^2.8 */
const uint8_t gamma_table[] = {
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,
  1,1,1,1,2,2,2,2,2,2,2,3,3,3,3,
  3,4,4,4,4,5,5,5,5,6,6,6,7,7,7,
  8,8,8,9,9,9,10,10,11,11,12,12,13,13,14,
  14,15,15,16,16,17,17,18,19,19,20,21,21,22,23,
  23,24,25,26,27,27,28,29,30,31,32,32,33,34,35,
  36,37,38,39,40,41,42,43,44,46,47,48,49,50,51,
  53,54,55,56,58,59,60,62,63 };


uint8_t value_to_pwm_level(float value, float max_value) {
    /* convert float value in [0, max_value] to pwm level */
    return gamma_table[(uint8_t) (value / max_value * 128)];
}


void clear_led_brightness() {
    for (uint16_t i=0; i < sizeof(led_status); i++) {
        led_status[i] = 0;
    }
}


uint8_t get_led_brightness(uint8_t row, uint8_t col) {
    uint16_t start_idx = (row * 9 + col) * PWM_BITS;
    uint8_t out = 0;
    
    for (uint8_t i=0; i < PWM_BITS; i++) {
        out += (!!(led_status[(start_idx + i) / 8] & (1 << ((start_idx + i) % 8)))) << i;
    }
    
    return out;
}

bool get_led_on(uint8_t row, uint8_t col) {
    uint16_t start_idx = (row * 9 + col) * PWM_BITS;
    return led_status[(start_idx) / 8] & (1 << (start_idx % 8));
}


void set_led_brightness(uint8_t row, uint8_t col, uint8_t val) {
    uint16_t start_idx = (row * 9 + col) * PWM_BITS;
    for (uint8_t i = 0; i < PWM_BITS; i++){
        if (val & (1 << i)) {
            led_status[(start_idx + i) / 8] |= (1 << ((start_idx + i) % 8));
        } else {
            led_status[(start_idx + i) / 8] &= ~(1 << ((start_idx + i) % 8));
        }
    }
}

/**
 * Filter LED Display
 */
void set_filter_leds(uint8_t filter_idx) {
   if (filter_idx & (1 << 0))   HAL_GPIO_WritePin(LED3_GPIO_Port, LED3_Pin, GPIO_PIN_RESET);
   else                         HAL_GPIO_WritePin(LED3_GPIO_Port, LED3_Pin, GPIO_PIN_SET);

   if (filter_idx & (1 << 1))   HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_RESET);
   else                         HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_SET);
   
   if (filter_idx & (1 << 2))   HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_RESET);
   else                         HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_SET);
   
   if (filter_idx & (1 << 3))   HAL_GPIO_WritePin(LED0_GPIO_Port, LED0_Pin, GPIO_PIN_RESET);
   else                         HAL_GPIO_WritePin(LED0_GPIO_Port, LED0_Pin, GPIO_PIN_SET);
}


void init_pwm_data() {
    // set column select shift pattern for first 8 cols
    // don't compute this dynamically to make pwm cycles more even
    for (uint8_t row=0; row < 9; row++) {
        row_shift_bytes[row] = (1 << row);
    }
}


void update_pwm_pattern() {
    for (uint8_t row=0; row <= 8; row++) {
        for (uint8_t col=0; col <= 8; col++) {
            uint8_t brightness = get_led_brightness(row, col);
            for (uint8_t pwm_index=0; pwm_index < PWM_LEVELS; pwm_index++) {
                if (pwm_index < brightness) {
                    col_shift_bytes[9 * pwm_index + row] |= (1 << (col));
                } else {
                    col_shift_bytes[9 * pwm_index + row] &= ~(1 << (col));
                }
            }
        }
    }
}

void turn_off_leds() {
    /* shift out pattern for all leds off*/
    /* wait for tx buffer ready*/
    ledmatrix_turnoff();
}

void run_pwm_cycle() {
    /* Run a full PWM cycle: PWM_LEVELS * 9 columns different output states */
    
    // turn on single leds
    for (uint8_t pwm_idx=0; pwm_idx < PWM_LEVELS; pwm_idx++) {
        for (uint8_t row=0; row <= 8; row++){
            ledmatrix_input(row_shift_bytes[row], col_shift_bytes[9 * pwm_idx + row]);
            //HAL_Delay(50);
            _delay_us(1);
            // ledmatrix_turnoff();
        }
    }
    // pulse SCK & set portc for last iteration  
    // turn off leds (otherwise last col is brighter
    // because of button scan time)
    turn_off_leds();
}
