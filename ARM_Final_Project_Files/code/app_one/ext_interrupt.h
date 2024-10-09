/*
 * ext_interrupt.h
 *
 *  Created on: Jul 26, 2024
 *      Author: Mina
 */

#ifndef EXT_INTERRUPT_H_
#define EXT_INTERRUPT_H_

#include"std_types.h"

#define NUM_OF_PORTS           6
#define NUM_OF_PINS_PER_PORT   8

/******************************************************************************
*                            User defined variables                           *
*******************************************************************************/


typedef enum{
    PORTA_ID,PORTB_ID,PORTC_ID,PORTD_ID,PORTE_ID,PORTF_ID
}GPIO_port;

/******************************************************************************
*                            Functions Prototypes                             *
*******************************************************************************/
void EXT_interrupte_Init(GPIO_port port_num, uint8 pin_num);

void EXT_interrupte_SetCallBack_A(volatile void (*Ptr) (void));
void EXT_interrupte_SetCallBack_B(volatile void (*Ptr) (void));
void EXT_interrupte_SetCallBack_C(volatile void (*Ptr) (void));
void EXT_interrupte_SetCallBack_D(volatile void (*Ptr) (void));
void EXT_interrupte_SetCallBack_E(volatile void (*Ptr) (void));
void EXT_interrupte_SetCallBack_F(volatile void (*Ptr) (void));

#endif /* EXT_INTERRUPT_H_ */
