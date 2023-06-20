/* 
 * File:   config.h
 * Author: kling
 *
 * Created on 27 September 2020, 17:59
 */

#ifndef CONFIG_H
#define	CONFIG_H

#include "stm32f4xx_hal.h"
#include "main.h"

#ifdef	__cplusplus
extern "C" {
#endif

// config options
#define DEBOUNCE_THRESHOLD 5
#define AUTO_SHUTDOWN_TIME_s 60 * 2 // 2 min

#define LED_COUNT (5 * 5 + 4 * 4 + 3 * 3 + 2 * 2 + 16 + 10 + 4)
#define PWM_BITS 6 /* NEED TO CHANGE gamma_table in led_status.c if this changes! */
#define N_FILTERS 16

    
#define PWM_LEVELS (1 << PWM_BITS)
#define MAX_PWM_LEVEL (PWM_LEVELS - 1)

#define     LED_L1_0_0      LED_MAT_0_0     //LED01
#define     LED_L1_0_1      LED_MAT_0_1     //LED02
#define     LED_L1_0_2      LED_MAT_0_2     //LED03
#define     LED_L1_0_3      LED_MAT_0_3     //LED04
#define     LED_L1_0_4      LED_MAT_0_4     //LED05
#define     LED_L1_1_0      LED_MAT_1_0     //LED10
#define     LED_L1_1_1      LED_MAT_1_1     //LED11
#define     LED_L1_1_2      LED_MAT_1_2     //LED12
#define     LED_L1_1_3      LED_MAT_1_3     //LED13
#define     LED_L1_1_4      LED_MAT_1_4     //LED14
#define     LED_L1_2_0      LED_MAT_2_0     //LED19
#define     LED_L1_2_1      LED_MAT_2_1     //LED20
#define     LED_L1_2_2      LED_MAT_2_2     //LED21
#define     LED_L1_2_3      LED_MAT_2_3     //LED22
#define     LED_L1_2_4      LED_MAT_2_4     //LED23
#define     LED_L1_3_0      LED_MAT_3_0     //LED28
#define     LED_L1_3_1      LED_MAT_3_1     //LED29
#define     LED_L1_3_2      LED_MAT_3_2     //LED30
#define     LED_L1_3_3      LED_MAT_3_3     //LED31
#define     LED_L1_3_4      LED_MAT_3_4     //LED32
#define     LED_L1_4_0      LED_MAT_4_0     //LED37
#define     LED_L1_4_1      LED_MAT_4_1     //LED38
#define     LED_L1_4_2      LED_MAT_4_2     //LED39
#define     LED_L1_4_3      LED_MAT_4_3     //LED40
#define     LED_L1_4_4      LED_MAT_4_4     //LED41
#define     LED_L2_0_0      LED_MAT_0_5     //LED06
#define     LED_L2_0_1      LED_MAT_0_6     //LED07
#define     LED_L2_0_2      LED_MAT_0_7     //LED08
#define     LED_L2_0_3      LED_MAT_0_8     //LED09
#define     LED_L2_1_0      LED_MAT_1_5     //LED15
#define     LED_L2_1_1      LED_MAT_1_6     //LED16
#define     LED_L2_1_2      LED_MAT_1_7     //LED17
#define     LED_L2_1_3      LED_MAT_1_8     //LED18
#define     LED_L2_2_0      LED_MAT_2_5     //LED24
#define     LED_L2_2_1      LED_MAT_2_6     //LED25
#define     LED_L2_2_2      LED_MAT_2_7     //LED26
#define     LED_L2_2_3      LED_MAT_2_8     //LED27
#define     LED_L2_3_0      LED_MAT_3_5     //LED33
#define     LED_L2_3_1      LED_MAT_3_6     //LED34
#define     LED_L2_3_2      LED_MAT_3_7     //LED35
#define     LED_L2_3_3      LED_MAT_3_8     //LED36
#define     LED_L3_0_0      LED_MAT_5_0     //LED46
#define     LED_L3_0_1      LED_MAT_5_1     //LED47
#define     LED_L3_0_2      LED_MAT_5_2     //LED48
#define     LED_L3_1_0      LED_MAT_6_0     //LED55
#define     LED_L3_1_1      LED_MAT_6_1     //LED56
#define     LED_L3_1_2      LED_MAT_6_2     //LED57
#define     LED_L3_2_0      LED_MAT_7_0     //LED64
#define     LED_L3_2_1      LED_MAT_7_1     //LED65
#define     LED_L3_2_2      LED_MAT_7_2     //LED66
#define     LED_L4_0_0      LED_MAT_5_3     //LED49
#define     LED_L4_0_1      LED_MAT_5_4     //LED50
#define     LED_L4_1_0      LED_MAT_6_3     //LED58
#define     LED_L4_1_1      LED_MAT_6_4     //LED59
#define     LED_L5_00       LED_MAT_4_5     //LED42
#define     LED_L5_01       LED_MAT_4_6     //LED43
#define     LED_L5_02       LED_MAT_4_7     //LED44
#define     LED_L5_03       LED_MAT_4_8     //LED45
#define     LED_L5_04       LED_MAT_5_5     //LED51
#define     LED_L5_05       LED_MAT_5_6     //LED52
#define     LED_L5_06       LED_MAT_5_7     //LED53
#define     LED_L5_07       LED_MAT_5_8     //LED54
#define     LED_L5_08       LED_MAT_6_5     //LED60
#define     LED_L5_09       LED_MAT_6_6     //LED61
#define     LED_L5_10       LED_MAT_6_7     //LED62
#define     LED_L5_11       LED_MAT_6_8     //LED63
#define     LED_L5_12       LED_MAT_7_5     //LED69
#define     LED_L5_13       LED_MAT_7_6     //LED70
#define     LED_L5_14       LED_MAT_7_7     //LED71
#define     LED_L5_15       LED_MAT_7_8     //LED72
#define     LED_L6_0        LED_MAT_8_8     //LED81
#define     LED_L6_1        LED_MAT_8_7     //LED80
#define     LED_L6_2        LED_MAT_8_6     //LED79
#define     LED_L6_3        LED_MAT_8_5     //LED78
#define     LED_L6_4        LED_MAT_8_0     //LED73
#define     LED_L6_5        LED_MAT_8_1     //LED74
#define     LED_L6_6        LED_MAT_8_2     //LED75
#define     LED_L6_7        LED_MAT_8_3     //LED76
#define     LED_L6_8        LED_MAT_8_4     //LED77
#define     LED_L6_9        LED_MAT_7_4     //LED68
#define     LED_L6_X        LED_MAT_7_3     //LED67

#define     LED_MAT_0_0     (1-1)
#define     LED_MAT_0_1     (2-1)
#define     LED_MAT_0_2     (3-1)
#define     LED_MAT_0_3     (4-1)
#define     LED_MAT_0_4     (5-1)
#define     LED_MAT_1_0     (10-1)
#define     LED_MAT_1_1     (11-1)
#define     LED_MAT_1_2     (12-1)
#define     LED_MAT_1_3     (13-1)
#define     LED_MAT_1_4     (14-1)
#define     LED_MAT_2_0     (19-1)
#define     LED_MAT_2_1     (20-1)
#define     LED_MAT_2_2     (21-1)
#define     LED_MAT_2_3     (22-1)
#define     LED_MAT_2_4     (23-1)
#define     LED_MAT_3_0     (28-1)
#define     LED_MAT_3_1     (29-1)
#define     LED_MAT_3_2     (30-1)
#define     LED_MAT_3_3     (31-1)
#define     LED_MAT_3_4     (32-1)
#define     LED_MAT_4_0     (37-1)
#define     LED_MAT_4_1     (38-1)
#define     LED_MAT_4_2     (39-1)
#define     LED_MAT_4_3     (40-1)
#define     LED_MAT_4_4     (41-1)
#define     LED_MAT_0_5     (6-1)
#define     LED_MAT_0_6     (7-1)
#define     LED_MAT_0_7     (8-1)
#define     LED_MAT_0_8     (9-1)
#define     LED_MAT_1_5     (15-1)
#define     LED_MAT_1_6     (16-1)
#define     LED_MAT_1_7     (17-1)
#define     LED_MAT_1_8     (18-1)
#define     LED_MAT_2_5     (24-1)
#define     LED_MAT_2_6     (25-1)
#define     LED_MAT_2_7     (26-1)
#define     LED_MAT_2_8     (27-1)
#define     LED_MAT_3_5     (33-1)
#define     LED_MAT_3_6     (34-1)
#define     LED_MAT_3_7     (35-1)
#define     LED_MAT_3_8     (36-1)
#define     LED_MAT_5_0     (46-1)
#define     LED_MAT_5_1     (47-1)
#define     LED_MAT_5_2     (48-1)
#define     LED_MAT_6_0     (55-1)
#define     LED_MAT_6_1     (56-1)
#define     LED_MAT_6_2     (57-1)
#define     LED_MAT_7_0     (64-1)
#define     LED_MAT_7_1     (65-1)
#define     LED_MAT_7_2     (66-1)
#define     LED_MAT_5_3     (49-1)
#define     LED_MAT_5_4     (50-1)
#define     LED_MAT_6_3     (58-1)
#define     LED_MAT_6_4     (59-1)
#define     LED_MAT_4_5     (42-1)
#define     LED_MAT_4_6     (43-1)
#define     LED_MAT_4_7     (44-1)
#define     LED_MAT_4_8     (45-1)
#define     LED_MAT_5_5     (51-1)
#define     LED_MAT_5_6     (52-1)
#define     LED_MAT_5_7     (53-1)
#define     LED_MAT_5_8     (54-1)
#define     LED_MAT_6_5     (60-1)
#define     LED_MAT_6_6     (61-1)
#define     LED_MAT_6_7     (62-1)
#define     LED_MAT_6_8     (63-1)
#define     LED_MAT_7_5     (69-1)
#define     LED_MAT_7_6     (70-1)
#define     LED_MAT_7_7     (71-1)
#define     LED_MAT_7_8     (72-1)
#define     LED_MAT_8_8     (81-1)
#define     LED_MAT_8_7     (80-1)
#define     LED_MAT_8_6     (79-1)
#define     LED_MAT_8_5     (78-1)
#define     LED_MAT_8_0     (73-1)
#define     LED_MAT_8_1     (74-1)
#define     LED_MAT_8_2     (75-1)
#define     LED_MAT_8_3     (76-1)
#define     LED_MAT_8_4     (77-1)
#define     LED_MAT_7_4     (68-1)
#define     LED_MAT_7_3     (67-1)


#ifdef	__cplusplus
}
#endif

#endif	/* CONFIG_H */

