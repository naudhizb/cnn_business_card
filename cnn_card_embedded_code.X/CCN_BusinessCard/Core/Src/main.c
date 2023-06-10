/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "fatfs.h"
#include "usb_device.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdint.h>
#include <usbd_cdc_if.h>
#include "led_matrix.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
SPI_HandleTypeDef hspi1;

TIM_HandleTypeDef htim1;
TIM_HandleTypeDef htim5;
TIM_HandleTypeDef htim10;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_SPI1_Init(void);
static void MX_TIM1_Init(void);
static void MX_TIM5_Init(void);
static void MX_TIM10_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

int _write(int file, char *ptr, int len){
    CDC_Transmit_FS((uint8_t *)ptr, len);
    return (len);
}

void display_demo()
{
	uint16_t row = 0, col = 0;

	row = 0xFFFF;
	col = 0x0001;
	for(int i = 0; i < 9; i++)
	{
		ledmatrix_input(row, col);
		col <<= 1;
		HAL_Delay(100);
	}
	row = 0x0001;
	col = 0xFFFF;
	for(int i = 0; i < 9; i++)
	{
		ledmatrix_input(row, col);
		row <<= 1;
		HAL_Delay(100);
	}
	ledmatrix_input(0, 0);
}

void display_demo2()
{
	ledmatrix_input((1 << 0), (1 << 0)); HAL_Delay(10); //  LED_L1_1_1 : LED_MAT_0_0 //LED01
	ledmatrix_input((1 << 0), (1 << 1)); HAL_Delay(10); //  LED_L1_1_2 : LED_MAT_0_1 //LED02
	ledmatrix_input((1 << 0), (1 << 2)); HAL_Delay(10); //  LED_L1_1_3 : LED_MAT_0_2 //LED03
	ledmatrix_input((1 << 0), (1 << 3)); HAL_Delay(10); //  LED_L1_1_4 : LED_MAT_0_3 //LED04
	ledmatrix_input((1 << 0), (1 << 4)); HAL_Delay(10); //  LED_L1_1_5 : LED_MAT_0_4 //LED05
	ledmatrix_input((1 << 1), (1 << 0)); HAL_Delay(10); //  LED_L1_2_1 : LED_MAT_1_0 //LED10
	ledmatrix_input((1 << 1), (1 << 1)); HAL_Delay(10); //  LED_L1_2_2 : LED_MAT_1_1 //LED11
	ledmatrix_input((1 << 1), (1 << 2)); HAL_Delay(10); //  LED_L1_2_3 : LED_MAT_1_2 //LED12
	ledmatrix_input((1 << 1), (1 << 3)); HAL_Delay(10); //  LED_L1_2_4 : LED_MAT_1_3 //LED13
	ledmatrix_input((1 << 1), (1 << 4)); HAL_Delay(10); //  LED_L1_2_5 : LED_MAT_1_4 //LED14
	ledmatrix_input((1 << 2), (1 << 0)); HAL_Delay(10); //  LED_L1_3_1 : LED_MAT_2_0 //LED19
	ledmatrix_input((1 << 2), (1 << 1)); HAL_Delay(10); //  LED_L1_3_2 : LED_MAT_2_1 //LED20
	ledmatrix_input((1 << 2), (1 << 2)); HAL_Delay(10); //  LED_L1_3_3 : LED_MAT_2_2 //LED21
	ledmatrix_input((1 << 2), (1 << 3)); HAL_Delay(10); //  LED_L1_3_4 : LED_MAT_2_3 //LED22
	ledmatrix_input((1 << 2), (1 << 4)); HAL_Delay(10); //  LED_L1_3_5 : LED_MAT_2_4 //LED23
	ledmatrix_input((1 << 3), (1 << 0)); HAL_Delay(10); //  LED_L1_4_1 : LED_MAT_3_0 //LED28
	ledmatrix_input((1 << 3), (1 << 1)); HAL_Delay(10); //  LED_L1_4_2 : LED_MAT_3_1 //LED29
	ledmatrix_input((1 << 3), (1 << 2)); HAL_Delay(10); //  LED_L1_4_3 : LED_MAT_3_2 //LED30
	ledmatrix_input((1 << 3), (1 << 3)); HAL_Delay(10); //  LED_L1_4_4 : LED_MAT_3_3 //LED31
	ledmatrix_input((1 << 3), (1 << 4)); HAL_Delay(10); //  LED_L1_4_5 : LED_MAT_3_4 //LED32
	ledmatrix_input((1 << 4), (1 << 0)); HAL_Delay(10); //  LED_L1_5_1 : LED_MAT_4_0 //LED37
	ledmatrix_input((1 << 4), (1 << 1)); HAL_Delay(10); //  LED_L1_5_2 : LED_MAT_4_1 //LED38
	ledmatrix_input((1 << 4), (1 << 2)); HAL_Delay(10); //  LED_L1_5_3 : LED_MAT_4_2 //LED39
	ledmatrix_input((1 << 4), (1 << 3)); HAL_Delay(10); //  LED_L1_5_4 : LED_MAT_4_3 //LED40
	ledmatrix_input((1 << 4), (1 << 4)); HAL_Delay(10); //  LED_L1_5_5 : LED_MAT_4_4 //LED41
	ledmatrix_input((1 << 0), (1 << 5)); HAL_Delay(10); //  LED_L2_1_1 : LED_MAT_0_5 //LED06
	ledmatrix_input((1 << 0), (1 << 6)); HAL_Delay(10); //  LED_L2_1_2 : LED_MAT_0_6 //LED07
	ledmatrix_input((1 << 0), (1 << 7)); HAL_Delay(10); //  LED_L2_1_3 : LED_MAT_0_7 //LED08
	ledmatrix_input((1 << 0), (1 << 8)); HAL_Delay(10); //  LED_L2_1_4 : LED_MAT_0_8 //LED09
	ledmatrix_input((1 << 1), (1 << 5)); HAL_Delay(10); //  LED_L2_2_1 : LED_MAT_1_5 //LED15
	ledmatrix_input((1 << 1), (1 << 6)); HAL_Delay(10); //  LED_L2_2_2 : LED_MAT_1_6 //LED16
	ledmatrix_input((1 << 1), (1 << 7)); HAL_Delay(10); //  LED_L2_2_3 : LED_MAT_1_7 //LED17
	ledmatrix_input((1 << 1), (1 << 8)); HAL_Delay(10); //  LED_L2_2_4 : LED_MAT_1_8 //LED18
	ledmatrix_input((1 << 2), (1 << 5)); HAL_Delay(10); //  LED_L2_3_1 : LED_MAT_2_5 //LED24
	ledmatrix_input((1 << 2), (1 << 6)); HAL_Delay(10); //  LED_L2_3_2 : LED_MAT_2_6 //LED25
	ledmatrix_input((1 << 2), (1 << 7)); HAL_Delay(10); //  LED_L2_3_3 : LED_MAT_2_7 //LED26
	ledmatrix_input((1 << 2), (1 << 8)); HAL_Delay(10); //  LED_L2_3_4 : LED_MAT_2_8 //LED27
	ledmatrix_input((1 << 3), (1 << 5)); HAL_Delay(10); //  LED_L2_4_1 : LED_MAT_3_5 //LED33
	ledmatrix_input((1 << 3), (1 << 6)); HAL_Delay(10); //  LED_L2_4_2 : LED_MAT_3_6 //LED34
	ledmatrix_input((1 << 3), (1 << 7)); HAL_Delay(10); //  LED_L2_4_3 : LED_MAT_3_7 //LED35
	ledmatrix_input((1 << 3), (1 << 8)); HAL_Delay(10); //  LED_L2_4_4 : LED_MAT_3_8 //LED36
	ledmatrix_input((1 << 5), (1 << 0)); HAL_Delay(10); //  LED_L3_1_1 : LED_MAT_5_0 // LED46
	ledmatrix_input((1 << 5), (1 << 1)); HAL_Delay(10); //  LED_L3_1_2 : LED_MAT_5_1 // LED47
	ledmatrix_input((1 << 5), (1 << 2)); HAL_Delay(10); //  LED_L3_1_3 : LED_MAT_5_2 // LED48
	ledmatrix_input((1 << 6), (1 << 0)); HAL_Delay(10); //  LED_L3_2_1 : LED_MAT_6_0 // LED55
	ledmatrix_input((1 << 6), (1 << 1)); HAL_Delay(10); //  LED_L3_2_2 : LED_MAT_6_1 // LED56
	ledmatrix_input((1 << 6), (1 << 2)); HAL_Delay(10); //  LED_L3_2_3 : LED_MAT_6_2 // LED57
	ledmatrix_input((1 << 7), (1 << 0)); HAL_Delay(10); //  LED_L3_3_1 : LED_MAT_7_0 // LED64
	ledmatrix_input((1 << 7), (1 << 1)); HAL_Delay(10); //  LED_L3_3_2 : LED_MAT_7_1 // LED65
	ledmatrix_input((1 << 7), (1 << 2)); HAL_Delay(10); //  LED_L3_3_3 : LED_MAT_7_2 // LED66
	ledmatrix_input((1 << 5), (1 << 3)); HAL_Delay(10); //  LED_L4_1_1 : LED_MAT_5_3 // LED49
	ledmatrix_input((1 << 5), (1 << 4)); HAL_Delay(10); //  LED_L4_1_2 : LED_MAT_5_4 // LED50
	ledmatrix_input((1 << 6), (1 << 3)); HAL_Delay(10); //  LED_L4_2_1 : LED_MAT_6_3 // LED58
	ledmatrix_input((1 << 6), (1 << 4)); HAL_Delay(10); //  LED_L4_2_2 : LED_MAT_6_4 // LED59
	ledmatrix_input((1 << 4), (1 << 5)); HAL_Delay(10); //  LED_L5_01 : LED_MAT_4_5 // LED42
	ledmatrix_input((1 << 4), (1 << 6)); HAL_Delay(10); //  LED_L5_02 : LED_MAT_4_6 // LED43
	ledmatrix_input((1 << 4), (1 << 7)); HAL_Delay(10); //  LED_L5_03 : LED_MAT_4_7 // LED44
	ledmatrix_input((1 << 4), (1 << 8)); HAL_Delay(10); //  LED_L5_04 : LED_MAT_4_8 // LED45
	ledmatrix_input((1 << 5), (1 << 5)); HAL_Delay(10); //  LED_L5_05 : LED_MAT_5_5 // LED51
	ledmatrix_input((1 << 5), (1 << 6)); HAL_Delay(10); //  LED_L5_06 : LED_MAT_5_6 // LED52
	ledmatrix_input((1 << 5), (1 << 7)); HAL_Delay(10); //  LED_L5_07 : LED_MAT_5_7 // LED53
	ledmatrix_input((1 << 5), (1 << 8)); HAL_Delay(10); //  LED_L5_08 : LED_MAT_5_8 // LED54
	ledmatrix_input((1 << 6), (1 << 5)); HAL_Delay(10); //  LED_L5_09 : LED_MAT_6_5 // LED60
	ledmatrix_input((1 << 6), (1 << 6)); HAL_Delay(10); //  LED_L5_10 : LED_MAT_6_6 // LED61
	ledmatrix_input((1 << 6), (1 << 7)); HAL_Delay(10); //  LED_L5_11 : LED_MAT_6_7 // LED62
	ledmatrix_input((1 << 6), (1 << 8)); HAL_Delay(10); //  LED_L5_12 : LED_MAT_6_8 // LED63
	ledmatrix_input((1 << 7), (1 << 5)); HAL_Delay(10); //  LED_L5_13 : LED_MAT_7_5 // LED69
	ledmatrix_input((1 << 7), (1 << 6)); HAL_Delay(10); //  LED_L5_14 : LED_MAT_7_6 // LED70
	ledmatrix_input((1 << 7), (1 << 7)); HAL_Delay(10); //  LED_L5_15 : LED_MAT_7_7 // LED71
	ledmatrix_input((1 << 7), (1 << 8)); HAL_Delay(10); //  LED_L5_16 : LED_MAT_7_8 // LED72
	ledmatrix_input((1 << 8), (1 << 8)); HAL_Delay(10); //  LED_L6_0 : LED_MAT_8_8 // LED81
	ledmatrix_input((1 << 8), (1 << 7)); HAL_Delay(10); //  LED_L6_1 : LED_MAT_8_7 // LED80
	ledmatrix_input((1 << 8), (1 << 6)); HAL_Delay(10); //  LED_L6_2 : LED_MAT_8_6 // LED79
	ledmatrix_input((1 << 8), (1 << 5)); HAL_Delay(10); //  LED_L6_3 : LED_MAT_8_5 // LED78
	ledmatrix_input((1 << 8), (1 << 0)); HAL_Delay(10); //  LED_L6_4 : LED_MAT_8_0 // LED73
	ledmatrix_input((1 << 8), (1 << 1)); HAL_Delay(10); //  LED_L6_5 : LED_MAT_8_1 // LED74
	ledmatrix_input((1 << 8), (1 << 2)); HAL_Delay(10); //  LED_L6_6 : LED_MAT_8_2 // LED75
	ledmatrix_input((1 << 8), (1 << 3)); HAL_Delay(10); //  LED_L6_7 : LED_MAT_8_3 // LED76
	ledmatrix_input((1 << 8), (1 << 4)); HAL_Delay(10); //  LED_L6_8 : LED_MAT_8_4 // LED77
	ledmatrix_input((1 << 7), (1 << 4)); HAL_Delay(10); //  LED_L6_9 : LED_MAT_7_4 // LED68
	ledmatrix_input((1 << 7), (1 << 3)); HAL_Delay(10); //  LED_L6_X : LED_MAT_7_3 // LED67
	ledmatrix_input(0, 0); HAL_Delay(10); //  LED_L6_X : LED_MAT_7_3 // LED67
}

#include "model/model.h"
#include "util/led_control.h"
#include "util/buttons.h"
#include "util/sleep.h"
#include "fun/startup_anim.h"
#include "fun/gol.h"

uint8_t filter_idx = 0;

void run_model_with_pwm() {
    // enable interrupt pwm during model calculations

    run_model_and_set_led_brightness(filter_idx);

    // disable interrupt pwm again
}


void reset_input_state() {
    filter_idx = 0;
    clear_led_brightness();
    set_led_brightness(1, 1, MAX_PWM_LEVEL);
    set_led_brightness(1, 2, MAX_PWM_LEVEL);
    set_led_brightness(2, 2, MAX_PWM_LEVEL);
    set_led_brightness(3, 1, MAX_PWM_LEVEL);
    set_led_brightness(3, 2, MAX_PWM_LEVEL);
    set_led_brightness(3, 3, MAX_PWM_LEVEL);
    
    set_filter_leds(filter_idx);
    update_pwm_pattern();
    
    run_model_with_pwm();
    update_pwm_pattern();
}


void sleep_and_reset() {
    turn_off_leds();
    go_to_sleep();
    display_demo();
    display_demo2();
    reset_input_state();
}

// Ref: https://michaeltien8901.github.io/2020/05/30/Jump-to-Internal-Bootloader-STM32F4.html
void JumpToBootloader(void) {
    void (*SysMemBootJump)(void);

    /**
     * Step: Set system memory address.
     *
     *       For STM32F429, system memory is on 0x1FFF 0000
     *       For other families, check AN2606 document table 110 with descriptions of memory addresses
     */
    volatile uint32_t addr = 0x1FFF0000;

    /**
     * Step: Disable RCC, set it to default (after reset) settings
     *       Internal clock, no PLL, etc.
     */
    HAL_RCC_DeInit();
    HAL_DeInit(); // add by ctien

    /**
     * Step: Disable systick timer and reset it to default values
     */
    SysTick->CTRL = 0;
    SysTick->LOAD = 0;
    SysTick->VAL = 0;

    /**
     * Step: Disable all interrupts
     */
  //  __disable_irq(); // changed by ctien

    /**
     * Step: Remap system memory to address 0x0000 0000 in address space
     *       For each family registers may be different.
     *       Check reference manual for each family.
     *
     *       For STM32F4xx, MEMRMP register in SYSCFG is used (bits[1:0])
     *       For STM32F0xx, CFGR1 register in SYSCFG is used (bits[1:0])
     *       For others, check family reference manual
     */
    //Remap by hand... {
#if defined(STM32F4)
    SYSCFG->MEMRMP = 0x01;
#endif
#if defined(STM32F0)
    SYSCFG->CFGR1 = 0x01;
#endif
    //} ...or if you use HAL drivers
    //__HAL_SYSCFG_REMAPMEMORY_SYSTEMFLASH();    //Call HAL macro to do this for you

    /**
     * Step: Set jump memory location for system memory
     *       Use address with 4 bytes offset which specifies jump location where program starts
     */
    SysMemBootJump = (void (*)(void)) (*((uint32_t *)(addr + 4)));

    /**
     * Step: Set main stack pointer.
     *       This step must be done last otherwise local variables in this function
     *       don't have proper value since stack pointer is located on different position
     *
     *       Set direct address location which specifies stack pointer in SRAM location
     */
    __set_MSP(*(uint32_t *)addr);

    /**
     * Step: Actually call our function to jump to set location
     *       This will start system memory execution
     */
    SysMemBootJump();

    /**
     * Step: Connect USB<->UART converter to dedicated USART pins and test
     *       and test with bootloader works with STM32 STM32 Cube Programmer
     */
}

void handle_buttons(){
    int8_t pressed = read_buttons();
    if (pressed == -1) {
        return;
    } else if (pressed == FILTER_BUTTON) {
        if (check_glider()) {
            run_gol();
        } else {
            filter_idx = (filter_idx + 1) % N_FILTERS;
        }
        run_model_with_pwm();
        set_filter_leds(filter_idx);
        update_pwm_pattern();
    } else if (pressed == PWR_BUTTON) {
      // If Long Press, jump to internal bootloader.(for update)
      uint32_t start_tick = HAL_GetTick();
      while(!!HAL_GPIO_ReadPin(B1_GPIO_Port, B1_Pin))
      {
        if (HAL_GetTick() > (start_tick + 5000))
        {
            JumpToBootloader();
        }
      }

        sleep_and_reset();
    } else {
        uint8_t row = pressed / 5;
        uint8_t col = pressed % 5;

        set_led_brightness(row, col,
            get_led_on(row, col) ? 0 : MAX_PWM_LEVEL
        );

        run_model_with_pwm();
        update_pwm_pattern();
    }
}

void main_loop() {
    
    while (1) {
        run_pwm_cycle();
        handle_buttons();
    }
}

void main_entry()
{   
    
    turn_off_leds();
    
    /* shift register output enable */
    
    init_pwm_data();
    
    // sleep
    sleep_and_reset();
    
    main_loop();
}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_SPI1_Init();
  MX_TIM1_Init();
  MX_TIM5_Init();
  MX_TIM10_Init();
  MX_FATFS_Init();
  MX_USB_DEVICE_Init();
  /* USER CODE BEGIN 2 */

  ledmatrix_turnoff();
  HAL_Delay(3000);
  printf("CNN Card Demo\r\n");

  ledmatrix_turnon();
  HAL_Delay(1000);

  main_entry();


  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 25;
  RCC_OscInitStruct.PLL.PLLN = 384;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV6;
  RCC_OscInitStruct.PLL.PLLQ = 8;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief SPI1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI1_Init(void)
{

  /* USER CODE BEGIN SPI1_Init 0 */

  /* USER CODE END SPI1_Init 0 */

  /* USER CODE BEGIN SPI1_Init 1 */

  /* USER CODE END SPI1_Init 1 */
  /* SPI1 parameter configuration*/
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_4;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI1_Init 2 */

  /* USER CODE END SPI1_Init 2 */

}

/**
  * @brief TIM1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM1_Init(void)
{

  /* USER CODE BEGIN TIM1_Init 0 */

  /* USER CODE END TIM1_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM1_Init 1 */

  /* USER CODE END TIM1_Init 1 */
  htim1.Instance = TIM1;
  htim1.Init.Prescaler = 0;
  htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim1.Init.Period = 65535;
  htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim1.Init.RepetitionCounter = 0;
  htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim1) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim1, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM1_Init 2 */

  /* USER CODE END TIM1_Init 2 */

}

/**
  * @brief TIM5 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM5_Init(void)
{

  /* USER CODE BEGIN TIM5_Init 0 */

  /* USER CODE END TIM5_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM5_Init 1 */

  /* USER CODE END TIM5_Init 1 */
  htim5.Instance = TIM5;
  htim5.Init.Prescaler = 0;
  htim5.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim5.Init.Period = 0xFFFFFF;
  htim5.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim5.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim5) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim5, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim5, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM5_Init 2 */

  /* USER CODE END TIM5_Init 2 */

}

/**
  * @brief TIM10 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM10_Init(void)
{

  /* USER CODE BEGIN TIM10_Init 0 */

  /* USER CODE END TIM10_Init 0 */

  TIM_OC_InitTypeDef sConfigOC = {0};

  /* USER CODE BEGIN TIM10_Init 1 */

  /* USER CODE END TIM10_Init 1 */
  htim10.Instance = TIM10;
  htim10.Init.Prescaler = 0;
  htim10.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim10.Init.Period = 0xFFFF;
  htim10.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim10.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim10) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_Init(&htim10) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_OnePulse_Init(&htim10, TIM_OPMODE_SINGLE) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim10, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM10_Init 2 */

  /* USER CODE END TIM10_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, LED_CTL_RCK_Pin|LED_CTL_SER_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, LED3_Pin|LED2_Pin|LED1_Pin|LED0_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, SPI1_CS_Pin|LED_CTL_OE_Pin|ROW_1_Pin|ROW_2_Pin
                          |ROW_3_Pin|ROW_4_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, ROW_5_Pin|LED_C8_Pin|LED_R8_Pin|LED_CTL_SCK_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : LED_CTL_RCK_Pin LED_CTL_SER_Pin */
  GPIO_InitStruct.Pin = LED_CTL_RCK_Pin|LED_CTL_SER_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : LED3_Pin LED2_Pin LED1_Pin LED0_Pin */
  GPIO_InitStruct.Pin = LED3_Pin|LED2_Pin|LED1_Pin|LED0_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : SPI1_CS_Pin */
  GPIO_InitStruct.Pin = SPI1_CS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(SPI1_CS_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : LED_CTL_OE_Pin ROW_1_Pin ROW_2_Pin ROW_3_Pin
                           ROW_4_Pin */
  GPIO_InitStruct.Pin = LED_CTL_OE_Pin|ROW_1_Pin|ROW_2_Pin|ROW_3_Pin
                          |ROW_4_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : ROW_5_Pin LED_C8_Pin LED_R8_Pin */
  GPIO_InitStruct.Pin = ROW_5_Pin|LED_C8_Pin|LED_R8_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : LED_CTL_SCK_Pin */
  GPIO_InitStruct.Pin = LED_CTL_SCK_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LED_CTL_SCK_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : COL_1_Pin COL_2_Pin COL_3_Pin COL_4_Pin
                           COL_5_Pin */
  GPIO_InitStruct.Pin = COL_1_Pin|COL_2_Pin|COL_3_Pin|COL_4_Pin
                          |COL_5_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : B0_Pin B1_Pin */
  GPIO_InitStruct.Pin = B0_Pin|B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM11 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM11) {
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */

  /* USER CODE END Callback 1 */
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
