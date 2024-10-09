/*
 * gpio.h
 *
 *  Created on: Jul 19, 2024
 *      Author: Mina
 */

#ifndef GPIO_H_
#define GPIO_H_

#include "std_types.h"


/****************************************************************************************************************************
 *                                                        Definitions
 ****************************************************************************************************************************/

#define NUM_OF_PORTS           6
#define NUM_OF_PINS_PER_PORT   8
#define PULL                PULL_UP
#define SIGNAL                DIGITAL

/****************************************************************************************************************************
 *                                                    User defined variables
 ****************************************************************************************************************************/
typedef enum{
    PORTA_ID,PORTB_ID,PORTC_ID,PORTD_ID,PORTE_ID,PORTF_ID
}GPIO_ports;


typedef enum
{
    PIN_INPUT=0,PIN_OUTPUT=1
}GPIO_PinDirectionType;

typedef enum
{
    PORT_INPUT=0x00,PORT_OUTPUT=0xFF
}GPIO_PortDirectionType;

typedef enum
{
    PULL_UP,PULL_DOWN
}GPIO_pulling;

typedef enum
{
    DIGITAL,ANALOG
}GPIO_signalType;

/****************************************************************************************************************************
 *                                                    Functions prototype
 ****************************************************************************************************************************/

/*
 * Description :
 * Setup the direction of the required pin input/output.
 * If the input port number or pin number are not correct, The function will not handle the request.
 */
void GPIO_setupPinDirection(uint8 port_num, uint8 pin_num, GPIO_PinDirectionType direction);

/*
 * Description :
 * Write the value Logic High or Logic Low on the required pin.
 * If the input port number or pin number are not correct, The function will not handle the request.
 * If the pin is input, this function will enable/disable the internal pull-up resistor.
 */
void GPIO_writePin(uint8 port_num, uint8 pin_num, uint8 value);

/*
 * Description :
 * TOGGLE the value Logic High or Logic Low on the required pin.
 * If the input port number or pin number are not correct, The function will not handle the request.
 * If the pin is input, this function will enable/disable the internal pull-up resistor.
 */
void GPIO_togglePin(GPIO_ports port_num, uint8 pin_num);

/*
 * Description :
 * Read and return the value for the required pin, it should be Logic High or Logic Low.
 * If the input port number or pin number are not correct, The function will return Logic Low.
 */
uint8 GPIO_readPin(uint8 port_num, uint8 pin_num);

/*
 * Description :
 * Setup the direction of the required port all pins input/output.
 * If the direction value is PORT_INPUT all pins in this port should be input pins.
 * If the direction value is PORT_OUTPUT all pins in this port should be output pins.
 * If the input port number is not correct, The function will not handle the request.
 */
void GPIO_setupPortDirection(uint8 port_num, GPIO_PortDirectionType direction);

/*
 * Description :
 * Write the value on the required port.
 * If any pin in the port is output pin the value will be written.
 * If any pin in the port is input pin this will activate/deactivate the internal pull-up resistor.
 * If the input port number is not correct, The function will not handle the request.
 */
void GPIO_writePort(uint8 port_num, uint8 value);

/*
 * Description :
 * Read and return the value of the required port.
 * If the input port number is not correct, The function will return ZERO value.
 */
uint8 GPIO_readPort(uint8 port_num);




#endif /* GPIO_H_ */
