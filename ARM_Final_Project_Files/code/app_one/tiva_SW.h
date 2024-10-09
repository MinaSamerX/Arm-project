/*
 * tiva_SW.h
 *
 *  Created on: Jul 13, 2024
 *      Author: Mina
 */

#ifndef TIVA_SW_H_
#define TIVA_SW_H_

#include"std_types.h"

#define SW_PORT PORTF_ID
#define PB_PRESSED 0
#define PB_NOT_PRESSED 1

typedef enum{
    SW1=4,SW2=0
}SW_no;


void SW_init( SW_no sw );
uint8 SW_check( SW_no sw);


#endif /* TIVA_SW_H_ */
