/*
 * led_matrix.h
 *
 *  Created on: Jun 5, 2023
 *      Author: Envie
 */

#ifndef SRC_LED_MATRIX_H_
#define SRC_LED_MATRIX_H_


#include <stdint.h>
void ledmatrix_turnoff();
void ledmatrix_turnon();
void ledmatrix_input(uint16_t row, uint16_t col);

#endif /* SRC_LED_MATRIX_H_ */
