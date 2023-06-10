#include "buttons.h"
#include "sleep.h"
#include "../config.h"

#include <stdint.h>

/**
 * returns pressed button index ROW*5 + COL
 *
 * if nothing returns -1
 */

int8_t read_button_matrix() {
    int8_t pressed = -1;
	for(int i = 0; i < 5; i++)
	{
		uint8_t data = 0;
		HAL_GPIO_WritePin(ROW_1_GPIO_Port, ROW_1_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(ROW_2_GPIO_Port, ROW_2_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(ROW_3_GPIO_Port, ROW_3_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(ROW_4_GPIO_Port, ROW_4_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(ROW_5_GPIO_Port, ROW_5_Pin, GPIO_PIN_RESET);
		switch(i)
		{
		case 0: HAL_GPIO_WritePin(ROW_1_GPIO_Port, ROW_1_Pin, GPIO_PIN_SET); break;
		case 1: HAL_GPIO_WritePin(ROW_2_GPIO_Port, ROW_2_Pin, GPIO_PIN_SET); break;
		case 2: HAL_GPIO_WritePin(ROW_3_GPIO_Port, ROW_3_Pin, GPIO_PIN_SET); break;
		case 3: HAL_GPIO_WritePin(ROW_4_GPIO_Port, ROW_4_Pin, GPIO_PIN_SET); break;
		case 4: HAL_GPIO_WritePin(ROW_5_GPIO_Port, ROW_5_Pin, GPIO_PIN_SET); break;
		default: break;
		}

		if(!!HAL_GPIO_ReadPin(COL_1_GPIO_Port, COL_1_Pin)) pressed = 5*i + 0;
		if(!!HAL_GPIO_ReadPin(COL_2_GPIO_Port, COL_2_Pin)) pressed = 5*i + 1;
		if(!!HAL_GPIO_ReadPin(COL_3_GPIO_Port, COL_3_Pin)) pressed = 5*i + 2;
		if(!!HAL_GPIO_ReadPin(COL_4_GPIO_Port, COL_4_Pin)) pressed = 5*i + 3;
		if(!!HAL_GPIO_ReadPin(COL_5_GPIO_Port, COL_5_Pin)) pressed = 5*i + 4;


        
        if (pressed != -1) {
            /* we stop at the first button */
            break;
        }

	}
    return pressed;
}





int8_t read_buttons() {
    static int8_t last_pressed = -1;
    static uint8_t debounce_counter = 0;
    
    int8_t pressed = read_button_matrix();
    
    if (pressed == -1) {
        // test power & filter buttons (separate GPIOs)
       if(!!HAL_GPIO_ReadPin(B0_GPIO_Port, B0_Pin)) {
           pressed = FILTER_BUTTON;
       }
       else if(!!HAL_GPIO_ReadPin(B1_GPIO_Port, B1_Pin)) {
           pressed = PWR_BUTTON;
       }
    }
    
    if (pressed != -1) {
        /* found a button press */
        
        /* reset auto shutdown counter */
        reset_rtc_cnt();
        
        if (pressed == last_pressed) {
            if (debounce_counter != HELD_FLAG){
                debounce_counter++;
            }
        } else {
            debounce_counter = 0;
            last_pressed = pressed;
        }
    } else {
        // no button press detected
        debounce_counter = 0;
        last_pressed = -1;
    }
    
    if (debounce_counter == DEBOUNCE_THRESHOLD) {
        debounce_counter = HELD_FLAG;
        return pressed;
    }
    
    return -1;
}
