/*
 * tiva_LEDS.h
 *
 *  Created on: Jul 13, 2024
 *      Author: Mina
 */

#ifndef TIVA_LEDS_H_
#define TIVA_LEDS_H_

#include"std_types.h"

//#define SYSTICK
//#define DELAY

#define PF1_PF2_PF3  (*((volatile unsigned long *)(0x40025000+0x38)))
#define LED_PORT PORTF_ID
#define DB_LED   4

typedef uint8 LED_color ;

typedef enum  {
    RED=1,BLUE=2,GREEN=3,MAGENTA=4,ORANGE=5,CYAN=6,WHITE=7,ALL =7
}color;
typedef enum {
    ON = 0 , OFF = 1
}LED_cond;

void LED_init( LED_color color);
void LED_status ( LED_color color , LED_cond status);
void set_oneLED(LED_color color);
void toggle_LED(LED_color color);
void rolling_init(void);
#ifdef DELAY
void LED_rolling_delay(uint64 D);
#endif
#ifdef SYSTICK
void LED_rolling_systick(uint32 D,uint8 count);
#endif

#endif /* TIVA_LEDS_H_ */
