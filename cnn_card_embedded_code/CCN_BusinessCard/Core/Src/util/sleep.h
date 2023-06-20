/* 
 * File:   sleep.h
 * Author: kling
 *
 * Created on 08 November 2020, 21:31
 */

#ifndef SLEEP_H
#define	SLEEP_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <stdint.h>

	void _delay_us(uint32_t us);
	void _delay_ms(uint32_t ms);
    void go_to_sleep();
    void reset_rtc_cnt();
    int check_rtc_elapsed();


#ifdef	__cplusplus
}
#endif

#endif	/* SLEEP_H */

