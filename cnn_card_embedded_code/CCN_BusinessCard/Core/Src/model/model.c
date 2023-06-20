#include "model.h"

#include "model_weights.h"
#include "tensor.h"
#include "../config.h"
#include "../util/led_control.h"

#include <math.h>

// todo: NEED TO MAP LED in This source

/**
 * Call template :
 * 
 * set_led_brightness_wrapper(LED_L1_0_0, value_to_pwm_level(t4_get_value(conv0_out, 0, 0, filter_idx, 0),conv0_activation_99per));
 *  
*/
void set_led_brightness_wrapper(uint32_t index, uint8_t value)
{
    // col, row, pwm_value
    set_led_brightness(index / 9, index % 9, value);
}

void set_output_led_brightness (
    struct float_4tensor *output
) {
    set_led_brightness_wrapper(LED_L6_0, value_to_pwm_level(output->data[1], 1.0));
    set_led_brightness_wrapper(LED_L6_1, value_to_pwm_level(output->data[2], 1.0));
    set_led_brightness_wrapper(LED_L6_2, value_to_pwm_level(output->data[3], 1.0));
    set_led_brightness_wrapper(LED_L6_3, value_to_pwm_level(output->data[4], 1.0));
    set_led_brightness_wrapper(LED_L6_4, value_to_pwm_level(output->data[5], 1.0));
    set_led_brightness_wrapper(LED_L6_5, value_to_pwm_level(output->data[6], 1.0));
    set_led_brightness_wrapper(LED_L6_6, value_to_pwm_level(output->data[7], 1.0));
    set_led_brightness_wrapper(LED_L6_7, value_to_pwm_level(output->data[8], 1.0));
    set_led_brightness_wrapper(LED_L6_8, value_to_pwm_level(output->data[9], 1.0));
    set_led_brightness_wrapper(LED_L6_9, value_to_pwm_level(output->data[0], 1.0));
    set_led_brightness_wrapper(LED_L6_X, 0);
}

void set_conv0_led_brightness (
    struct float_4tensor *conv0_out,
    uint8_t filter_idx
) {
    if (filter_idx >= 4) {
        set_led_brightness_wrapper(LED_L2_0_0, 0);
        set_led_brightness_wrapper(LED_L2_0_1, 0);
        set_led_brightness_wrapper(LED_L2_0_2, 0);
        set_led_brightness_wrapper(LED_L2_0_3, 0);
        set_led_brightness_wrapper(LED_L2_1_0, 0);
        set_led_brightness_wrapper(LED_L2_1_1, 0);
        set_led_brightness_wrapper(LED_L2_1_2, 0);
        set_led_brightness_wrapper(LED_L2_1_3, 0);
        set_led_brightness_wrapper(LED_L2_2_0, 0);
        set_led_brightness_wrapper(LED_L2_2_1, 0);
        set_led_brightness_wrapper(LED_L2_2_2, 0);
        set_led_brightness_wrapper(LED_L2_2_3, 0);
        set_led_brightness_wrapper(LED_L2_3_0, 0);
        set_led_brightness_wrapper(LED_L2_3_1, 0);
        set_led_brightness_wrapper(LED_L2_3_2, 0);
        set_led_brightness_wrapper(LED_L2_3_3, 0);
        return;
    }

    set_led_brightness_wrapper(LED_L2_0_0, value_to_pwm_level(t4_get_value(conv0_out, 0, 0, filter_idx, 0),conv0_activation_99per));
    set_led_brightness_wrapper(LED_L2_0_1, value_to_pwm_level(t4_get_value(conv0_out, 1, 0, filter_idx, 0),conv0_activation_99per));
    set_led_brightness_wrapper(LED_L2_0_2, value_to_pwm_level(t4_get_value(conv0_out, 2, 0, filter_idx, 0),conv0_activation_99per));
    set_led_brightness_wrapper(LED_L2_0_3, value_to_pwm_level(t4_get_value(conv0_out, 3, 0, filter_idx, 0),conv0_activation_99per));
    set_led_brightness_wrapper(LED_L2_1_0, value_to_pwm_level(t4_get_value(conv0_out, 0, 1, filter_idx, 0),conv0_activation_99per));
    set_led_brightness_wrapper(LED_L2_1_1, value_to_pwm_level(t4_get_value(conv0_out, 1, 1, filter_idx, 0),conv0_activation_99per));
    set_led_brightness_wrapper(LED_L2_1_2, value_to_pwm_level(t4_get_value(conv0_out, 2, 1, filter_idx, 0),conv0_activation_99per));
    set_led_brightness_wrapper(LED_L2_1_3, value_to_pwm_level(t4_get_value(conv0_out, 3, 1, filter_idx, 0),conv0_activation_99per));
    set_led_brightness_wrapper(LED_L2_2_0, value_to_pwm_level(t4_get_value(conv0_out, 0, 2, filter_idx, 0),conv0_activation_99per));
    set_led_brightness_wrapper(LED_L2_2_1, value_to_pwm_level(t4_get_value(conv0_out, 1, 2, filter_idx, 0),conv0_activation_99per));
    set_led_brightness_wrapper(LED_L2_2_2, value_to_pwm_level(t4_get_value(conv0_out, 2, 2, filter_idx, 0),conv0_activation_99per));
    set_led_brightness_wrapper(LED_L2_2_3, value_to_pwm_level(t4_get_value(conv0_out, 3, 2, filter_idx, 0),conv0_activation_99per));
    set_led_brightness_wrapper(LED_L2_3_0, value_to_pwm_level(t4_get_value(conv0_out, 0, 3, filter_idx, 0),conv0_activation_99per));
    set_led_brightness_wrapper(LED_L2_3_1, value_to_pwm_level(t4_get_value(conv0_out, 1, 3, filter_idx, 0),conv0_activation_99per));
    set_led_brightness_wrapper(LED_L2_3_2, value_to_pwm_level(t4_get_value(conv0_out, 2, 3, filter_idx, 0),conv0_activation_99per));
    set_led_brightness_wrapper(LED_L2_3_3, value_to_pwm_level(t4_get_value(conv0_out, 3, 3, filter_idx, 0),conv0_activation_99per));
}

/**
 *  01234567
 * 501234567
 * 
 *  8
 * 08
 * 19
*/
void set_conv1_led_brightness (
    struct float_4tensor *conv1_out,
    uint8_t filter_idx
) {
    if (filter_idx >= 8) {
        set_led_brightness_wrapper(LED_L3_0_0, 0);
        set_led_brightness_wrapper(LED_L3_0_1, 0);
        set_led_brightness_wrapper(LED_L3_0_2, 0);
        set_led_brightness_wrapper(LED_L3_1_0, 0);
        set_led_brightness_wrapper(LED_L3_1_1, 0);
        set_led_brightness_wrapper(LED_L3_1_2, 0);
        set_led_brightness_wrapper(LED_L3_2_0, 0);
        set_led_brightness_wrapper(LED_L3_2_1, 0);
        set_led_brightness_wrapper(LED_L3_2_2, 0);
        return;
    }

    set_led_brightness_wrapper(LED_L3_0_0, value_to_pwm_level(t4_get_value(conv1_out, 0, 0, filter_idx, 0),conv1_activation_99per));
    set_led_brightness_wrapper(LED_L3_0_1, value_to_pwm_level(t4_get_value(conv1_out, 1, 0, filter_idx, 0),conv1_activation_99per));
    set_led_brightness_wrapper(LED_L3_0_2, value_to_pwm_level(t4_get_value(conv1_out, 2, 0, filter_idx, 0),conv1_activation_99per));
    set_led_brightness_wrapper(LED_L3_1_0, value_to_pwm_level(t4_get_value(conv1_out, 0, 1, filter_idx, 0),conv1_activation_99per));
    set_led_brightness_wrapper(LED_L3_1_1, value_to_pwm_level(t4_get_value(conv1_out, 1, 1, filter_idx, 0),conv1_activation_99per));
    set_led_brightness_wrapper(LED_L3_1_2, value_to_pwm_level(t4_get_value(conv1_out, 2, 1, filter_idx, 0),conv1_activation_99per));
    set_led_brightness_wrapper(LED_L3_2_0, value_to_pwm_level(t4_get_value(conv1_out, 0, 2, filter_idx, 0),conv1_activation_99per));
    set_led_brightness_wrapper(LED_L3_2_1, value_to_pwm_level(t4_get_value(conv1_out, 1, 2, filter_idx, 0),conv1_activation_99per));
    set_led_brightness_wrapper(LED_L3_2_2, value_to_pwm_level(t4_get_value(conv1_out, 2, 2, filter_idx, 0),conv1_activation_99per));
}

/**
 *   2345
 * 8 0123
*/
void set_conv2_led_brightness (
    struct float_4tensor *conv2_out,
    uint8_t filter_idx
) {
    set_led_brightness_wrapper(LED_L4_0_0, value_to_pwm_level(t4_get_value(conv2_out, 0, 0, filter_idx, 0),conv2_activation_99per));
    set_led_brightness_wrapper(LED_L4_0_1, value_to_pwm_level(t4_get_value(conv2_out, 1, 0, filter_idx, 0),conv2_activation_99per));
    set_led_brightness_wrapper(LED_L4_1_0, value_to_pwm_level(t4_get_value(conv2_out, 0, 1, filter_idx, 0),conv2_activation_99per));
    set_led_brightness_wrapper(LED_L4_1_1, value_to_pwm_level(t4_get_value(conv2_out, 1, 1, filter_idx, 0),conv2_activation_99per));
}


void set_pool_led_brightness (
    struct float_4tensor *pool_out
) {
    set_led_brightness_wrapper(LED_L5_00, value_to_pwm_level(t4_get_value(pool_out,  0, 0, 0, 0),conv2_activation_99per));
    set_led_brightness_wrapper(LED_L5_01, value_to_pwm_level(t4_get_value(pool_out,  1, 0, 0, 0),conv2_activation_99per));
    set_led_brightness_wrapper(LED_L5_02, value_to_pwm_level(t4_get_value(pool_out,  2, 0, 0, 0),conv2_activation_99per));
    set_led_brightness_wrapper(LED_L5_03, value_to_pwm_level(t4_get_value(pool_out,  3, 0, 0, 0),conv2_activation_99per));
    set_led_brightness_wrapper(LED_L5_04, value_to_pwm_level(t4_get_value(pool_out,  4, 0, 0, 0),conv2_activation_99per));
    set_led_brightness_wrapper(LED_L5_05, value_to_pwm_level(t4_get_value(pool_out,  5, 0, 0, 0),conv2_activation_99per));
    set_led_brightness_wrapper(LED_L5_06, value_to_pwm_level(t4_get_value(pool_out,  6, 0, 0, 0),conv2_activation_99per));
    set_led_brightness_wrapper(LED_L5_07, value_to_pwm_level(t4_get_value(pool_out,  7, 0, 0, 0),conv2_activation_99per));
    set_led_brightness_wrapper(LED_L5_08, value_to_pwm_level(t4_get_value(pool_out,  8, 0, 0, 0),conv2_activation_99per));
    set_led_brightness_wrapper(LED_L5_09, value_to_pwm_level(t4_get_value(pool_out,  9, 0, 0, 0),conv2_activation_99per));
    set_led_brightness_wrapper(LED_L5_10, value_to_pwm_level(t4_get_value(pool_out, 10, 0, 0, 0),conv2_activation_99per));
    set_led_brightness_wrapper(LED_L5_11, value_to_pwm_level(t4_get_value(pool_out, 11, 0, 0, 0),conv2_activation_99per));
    set_led_brightness_wrapper(LED_L5_12, value_to_pwm_level(t4_get_value(pool_out, 12, 0, 0, 0),conv2_activation_99per));
    set_led_brightness_wrapper(LED_L5_13, value_to_pwm_level(t4_get_value(pool_out, 13, 0, 0, 0),conv2_activation_99per));
    set_led_brightness_wrapper(LED_L5_14, value_to_pwm_level(t4_get_value(pool_out, 14, 0, 0, 0),conv2_activation_99per));
    set_led_brightness_wrapper(LED_L5_15, value_to_pwm_level(t4_get_value(pool_out, 15, 0, 0, 0),conv2_activation_99per));
}


float t_in_conv1_out_pool_out_data[3 * 3 * 8] = {0};
float conv02_out_data[4 * 4 * 4] = {0};
float t_out_data[10] = {0};

struct float_4tensor t_in = {
    .data=(float*) t_in_conv1_out_pool_out_data,
    .s0=5, // rows
    .s1=5, // cols
    .s2=1,
    .s3=1
};


struct float_4tensor conv0_out = {
    .data=(float*) conv02_out_data,
    .s0=4, // rows
    .s1=4, // cols
    .s2=4, // channels
    .s3=1
};


struct float_4tensor conv1_out = {
    .data=(float*) t_in_conv1_out_pool_out_data,
    .s0=3, // rows
    .s1=3, // cols
    .s2=8, // channels
    .s3=1
};

struct float_4tensor conv2_out = {
    /* reuse conv0_out data (both 64 floats)*/
    .data=(float*) conv02_out_data,
    .s0=2, // rows
    .s1=2, // cols
    .s2=16, // channels
    .s3=1
};


struct float_4tensor pool_out = {
    .data=(float*) t_in_conv1_out_pool_out_data,
    .s0=16, // channels
    .s1=1,
    .s2=1,
    .s3=1
};


struct float_4tensor t_out = {
    .data=(float*) t_out_data,
    .s0=10, // channels
    .s1=1,
    .s2=1,
    .s3=1
};


void run_model_and_set_led_brightness(uint8_t filter_idx) {
    for (uint8_t row=0; row < 5; row++) {
        for (uint8_t col=0; col < 5; col++) {
            t4_set_value(&t_in, row, col, 0, 0,
                         !!get_led_brightness(row, col));
        }
    }

    t4_convolve_2x2(&t_in, &conv0_kernel, &conv0_out);
    t4_add_conv_bias(&conv0_out, &conv0_bias);
    t4_relu(&conv0_out);
    
    set_conv0_led_brightness(&conv0_out, filter_idx);
 
    
    t4_convolve_2x2(&conv0_out, &conv1_kernel, &conv1_out);
    t4_add_conv_bias(&conv1_out, &conv1_bias);
    t4_relu(&conv1_out);
    
    set_conv1_led_brightness(&conv1_out, filter_idx);
    
    
    t4_convolve_2x2(&conv1_out, &conv2_kernel, &conv2_out);
    t4_add_conv_bias(&conv2_out, &conv2_bias);
    t4_relu(&conv2_out);
   
    set_conv2_led_brightness(&conv2_out, filter_idx);
    
    t4_max_pool(&conv2_out, &pool_out);
    set_pool_led_brightness(&pool_out);
    
    t4_matrix_mult(&dense_kernel, &pool_out, &t_out);
    t4_add(&t_out, &dense_bias);
    t4_softmax(&t_out);
    
    
    set_output_led_brightness(&t_out);
}
