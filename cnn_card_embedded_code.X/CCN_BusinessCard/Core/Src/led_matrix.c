/*
 * led_ledmatrix.c
 *
 *  Created on: Jun 5, 2023
 *      Author: Envie
 */

#include <stdio.h>
#include "led_matrix.h"
#include "main.h"
#include "cmsis_compiler.h"

#define MATRIX_SIZE 9

__INLINE void ledmatrix_latch();
__INLINE void ledmatrix_shift();
__INLINE void ledmatrix_data(uint8_t data);

__INLINE void ledmatrix_latch()
{
	// PIN12: STCP(STorage register Clock input Pin) --> SCK
	HAL_GPIO_WritePin(LED_CTL_SCK_GPIO_Port, LED_CTL_SCK_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(LED_CTL_SCK_GPIO_Port, LED_CTL_SCK_Pin, GPIO_PIN_RESET);
}
__INLINE void ledmatrix_shift()
{
	// PIN 11: SHCP(SHift register Clock input Pin)--> RCK
	HAL_GPIO_WritePin(LED_CTL_RCK_GPIO_Port, LED_CTL_RCK_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(LED_CTL_RCK_GPIO_Port, LED_CTL_RCK_Pin, GPIO_PIN_RESET);
}
__INLINE void ledmatrix_data(uint8_t data)
{
	if(data)
	{
		HAL_GPIO_WritePin(LED_CTL_SER_GPIO_Port, LED_CTL_SER_Pin, GPIO_PIN_SET);
	} else {
		HAL_GPIO_WritePin(LED_CTL_SER_GPIO_Port, LED_CTL_SER_Pin, GPIO_PIN_RESET);
	}
}

void ledmatrix_turnoff()
{
	HAL_GPIO_WritePin(LED_C8_GPIO_Port, LED_C8_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(LED_CTL_OE_GPIO_Port, LED_CTL_OE_Pin, GPIO_PIN_SET); // NOE
	HAL_GPIO_WritePin(LED_R8_GPIO_Port, LED_R8_Pin, GPIO_PIN_RESET);
}

static int32_t LED_R8 = 0;
static int32_t LED_C8 = 1;

void ledmatrix_turnon()
{
	HAL_GPIO_WritePin(LED_R8_GPIO_Port, LED_R8_Pin, LED_R8);
	ledmatrix_latch();
	HAL_GPIO_WritePin(LED_CTL_OE_GPIO_Port, LED_CTL_OE_Pin, GPIO_PIN_RESET); // NOE
	HAL_GPIO_WritePin(LED_C8_GPIO_Port, LED_C8_Pin, LED_C8);
}

void ledmatrix_input(uint16_t row, uint16_t col)
{
//	printf("0x%04X 0x%04X\r\n", row, col);
	/*
	 *  GPIO
	 *   |
	 *   v
	 * R 8 7654 3210
	 * C 8 7654 3210
	 *
	 * Input Sequence : C7654 3210 R7654 3210
	 */

	col = ~col; // Column Active Low.
	uint8_t data = 0;
	uint32_t acc = 0;
	for (int i = 7; 0 <= i; i--)
	{
		data = col & (1 << i);
		ledmatrix_data(col & (1 << i));
		ledmatrix_shift();
		acc |= data;
		acc <<= 1;
	}
	for (int i = 7; 0 <= i; i--)
	{
		data = row & (1 << i);
		ledmatrix_data(row & (1 << i));
		ledmatrix_shift();
		acc |= data;
		acc <<= 1;
	}

	// turn on
	// HAL_GPIO_WritePin(LED_R8_GPIO_Port, LED_R8_Pin, !!(row & (1 << 8)));
	// HAL_GPIO_WritePin(LED_C8_GPIO_Port, LED_C8_Pin, !!(col & (1 << 8)));
	LED_R8 =  !!(row & (1 << 8));
	LED_C8 =  !!(col & (1 << 8));
	ledmatrix_turnon();
}

