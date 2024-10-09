/*
 * tiva_SW.c
 *
 *  Created on: Jul 13, 2024
 *      Author: Mina
 */
#include "tiva_SW.h"
#include"gpio.h"

void SW_init(SW_no sw)
{
    GPIO_setupPinDirection(SW_PORT,sw,PIN_INPUT);
}

uint8 SW_check(SW_no sw){

    return GPIO_readPin(SW_PORT,sw);
}
