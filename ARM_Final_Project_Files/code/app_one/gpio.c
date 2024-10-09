/*
 * gpio.c
 *
 *  Created on: Jul 19, 2024
 *      Author: Mina
 */


#include "gpio.h"
#include "tm4c123gh6pm_registers.h"

void GPIO_setupPinDirection(GPIO_ports port_num, uint8 pin_num, GPIO_PinDirectionType direction){

    if((pin_num >= NUM_OF_PINS_PER_PORT) || (port_num >= NUM_OF_PORTS))
    {
        /* Do Nothing */
    }
    else
    {
        /* Setup the pin direction as required */

        SYSCTL_RCGCGPIO_REG |= (1<<port_num); // enable clock for PORT

        while((SYSCTL_PRGPIO_REG&(1<<port_num)) == 0){}; // make sure that the clock enabled for PORT




        switch(port_num)
        {
        case PORTA_ID:
#if SIGNAL == DIGITAL
            GPIO_PORTA_DEN_REG   |=  (1<<pin_num); // Digital enable
            GPIO_PORTA_AMSEL_REG &= ~(1<<pin_num); // Analog disable
#else
            GPIO_PORTA_DEN_REG   &= ~(1<<pin_num); // Digital disable
            GPIO_PORTA_AMSEL_REG |= (1<<pin_num); // Analog enable
#endif


            GPIO_PORTA_AFSEL_REG &= ~(1<<pin_num); // Alternative function disable

            switch(direction){

            case PIN_INPUT:
                GPIO_PORTA_DIR_REG &= ~(1<<pin_num);// set up direction input
#if PULL == PULL_UP
                GPIO_PORTA_PUR_REG |= (1<<pin_num);

#else
                GPIO_PORTA_PDR_REG |= (1<<pin_num);

#endif
                break;
            case PIN_OUTPUT:
                GPIO_PORTA_DIR_REG |= (1<<pin_num);// set up direction output
                GPIO_PORTA_DATA_REG  &= ~(1<<pin_num);      /* Clear bit in Data register to turn off initially */
                break;
            default:
                GPIO_PORTA_DIR_REG |= (1<<pin_num);// set up direction output
                GPIO_PORTA_DATA_REG  &= ~(1<<pin_num);      /* Clear bit in Data register to turn off initially */
            }
            break;

            case PORTB_ID:

#if SIGNAL == DIGITAL
                GPIO_PORTB_DEN_REG   |=  (1<<pin_num); // Digital enable
                GPIO_PORTB_AMSEL_REG &= ~(1<<pin_num); // Analog disable
#else
                GPIO_PORTB_DEN_REG   &= ~(1<<pin_num); // Digital disable
                GPIO_PORTB_AMSEL_REG |= (1<<pin_num); // Analog enable
#endif
                GPIO_PORTB_AFSEL_REG &= ~(1<<pin_num); // Alternative function disable


                switch(direction){

                case PIN_INPUT:
                    GPIO_PORTB_DIR_REG &= ~(1<<pin_num);// set up direction input
#if PULL == PULL_UP
                    GPIO_PORTB_PUR_REG |= (1<<pin_num);

#else
                    GPIO_PORTB_PDR_REG |= (1<<pin_num);

#endif
                    break;
                case PIN_OUTPUT:
                    GPIO_PORTB_DIR_REG |= (1<<pin_num);// set up direction output
                    GPIO_PORTB_DATA_REG  &= ~(1<<pin_num);      /* Clear bit in Data register to turn off initially */
                    break;
                default:
                    GPIO_PORTB_DIR_REG |= (1<<pin_num);// set up direction output
                    GPIO_PORTB_DATA_REG  &= ~(1<<pin_num);      /* Clear bit in Data register to turn off initially */
                }
                break;

                case PORTC_ID:

                    /* From pin 0 to pin 3 in port c : JTAG pins please don't use them */
                    if(pin_num <= 3){
                        break;
                    }

#if SIGNAL == DIGITAL
                    GPIO_PORTC_DEN_REG   |=  (1<<pin_num); // Digital enable
                    GPIO_PORTC_AMSEL_REG &= ~(1<<pin_num); // Analog disable
#else
                    GPIO_PORTC_DEN_REG   &= ~(1<<pin_num); // Digital disable
                    GPIO_PORTC_AMSEL_REG |= (1<<pin_num); // Analog enable
#endif
                    GPIO_PORTC_AFSEL_REG &= ~(1<<pin_num); // Alternative function disable

                    switch(direction){

                    case PIN_INPUT:
                        GPIO_PORTC_DIR_REG &= ~(1<<pin_num);// set up direction input
#if PULL == PULL_UP
                        GPIO_PORTC_PUR_REG |= (1<<pin_num);

#else
                        GPIO_PORTC_PDR_REG |= (1<<pin_num);

#endif
                        break;
                    case PIN_OUTPUT:
                        GPIO_PORTC_DIR_REG |= (1<<pin_num);// set up direction output
                        GPIO_PORTC_DATA_REG  &= ~(1<<pin_num);      /* Clear bit in Data register to turn off initially */
                        break;
                    default:
                        GPIO_PORTC_DIR_REG |= (1<<pin_num);// set up direction output
                        GPIO_PORTC_DATA_REG  &= ~(1<<pin_num);      /* Clear bit in Data register to turn off initially */
                    }

                    break;

                    case PORTD_ID:

                        /* This is NMI pin so we need to unlock and commit it first */
                        if(pin_num == 7){

                            GPIO_PORTD_LOCK_REG = 0x4C4F434B;
                            GPIO_PORTD_CR_REG |= (1<<pin_num);
                        }

#if SIGNAL == DIGITAL
                        GPIO_PORTD_DEN_REG   |=  (1<<pin_num); // Digital enable
                        GPIO_PORTD_AMSEL_REG &= ~(1<<pin_num); // Analog disable
#else
                        GPIO_PORTD_DEN_REG   &= ~(1<<pin_num); // Digital disable
                        GPIO_PORTD_AMSEL_REG |= (1<<pin_num); // Analog enable
#endif
                        GPIO_PORTD_AFSEL_REG &= ~(1<<pin_num);  // Alternative function disable


                        switch(direction){

                        case PIN_INPUT:
                            GPIO_PORTD_DIR_REG &= ~(1<<pin_num);// set up direction input
#if PULL == PULL_UP
                            GPIO_PORTD_PUR_REG |= (1<<pin_num);

#else
                            GPIO_PORTD_PDR_REG |= (1<<pin_num);

#endif
                            break;
                        case PIN_OUTPUT:
                            GPIO_PORTD_DIR_REG |= (1<<pin_num);// set up direction output
                            GPIO_PORTD_DATA_REG  &= ~(1<<pin_num);      /* Clear bit in Data register to turn off initially */
                            break;
                        default:
                            GPIO_PORTD_DIR_REG |= (1<<pin_num);// set up direction output
                            GPIO_PORTD_DATA_REG  &= ~(1<<pin_num);      /* Clear bit in Data register to turn off initially */
                        }
                        break;

                        case PORTE_ID:

#if SIGNAL == DIGITAL
                            GPIO_PORTE_DEN_REG   |=  (1<<pin_num); // Digital enable
                            GPIO_PORTE_AMSEL_REG &= ~(1<<pin_num); // Analog disable
#else
                            GPIO_PORTE_DEN_REG   &= ~(1<<pin_num); // Digital disable
                            GPIO_PORTE_AMSEL_REG |= (1<<pin_num); // Analog enable
#endif
                            GPIO_PORTE_AFSEL_REG &= ~(1<<pin_num);  // Alternative function disable


                            switch(direction){

                            case PIN_INPUT:
                                GPIO_PORTE_DIR_REG &= ~(1<<pin_num);// set up direction input
#if PULL == PULL_UP
                                GPIO_PORTE_PUR_REG |= (1<<pin_num);

#else
                                GPIO_PORTE_PDR_REG |= (1<<pin_num);

#endif
                                break;
                            case PIN_OUTPUT:
                                GPIO_PORTE_DIR_REG |= (1<<pin_num);// set up direction output
                                GPIO_PORTE_DATA_REG  &= ~(1<<pin_num);      /* Clear bit in Data register to turn off initially */
                                break;
                            default:
                                GPIO_PORTE_DIR_REG |= (1<<pin_num);// set up direction output
                                GPIO_PORTE_DATA_REG  &= ~(1<<pin_num);      /* Clear bit in Data register to turn off initially */
                            }
                            break;

                            case PORTF_ID:

                                /* This is NMI pin so we need to unlock and commit it first */
                                if(pin_num == 0){

                                    GPIO_PORTF_LOCK_REG = 0x4C4F434B;
                                    GPIO_PORTF_CR_REG |= (1<< pin_num);
                                }

#if SIGNAL == DIGITAL
                                GPIO_PORTF_DEN_REG   |=  (1<<pin_num); // Digital enable
                                GPIO_PORTF_AMSEL_REG &= ~(1<<pin_num); // Analog disable
#else
                                GPIO_PORTF_DEN_REG   &= ~(1<<pin_num); // Digital disable
                                GPIO_PORTF_AMSEL_REG |= (1<<pin_num); // Analog enable
#endif
                                GPIO_PORTF_AFSEL_REG &= ~(1<<pin_num);  // Alternative function disable

                                switch(direction){

                                case PIN_INPUT:
                                    GPIO_PORTF_DIR_REG &= ~(1<<pin_num);// set up direction input
#if PULL == PULL_UP
                                    GPIO_PORTF_PUR_REG |= (1<<pin_num);

#else
                                    GPIO_PORTF_PDR_REG |= (1<<pin_num);
#endif
                                    break;
                                case PIN_OUTPUT:
                                    GPIO_PORTF_DIR_REG |= (1<<pin_num);// set up direction output
                                    GPIO_PORTF_DATA_REG  &= ~(1<<pin_num);      /* Clear bit in Data register to turn off initially */
                                    break;
                                default:
                                    GPIO_PORTF_DIR_REG |= (1<<pin_num);// set up direction output
                                    GPIO_PORTF_DATA_REG  &= ~(1<<pin_num);      /* Clear bit in Data register to turn off initially */
                                }
                                break;

                                default :
                                    break;

        }
    }
}


void GPIO_writePin(GPIO_ports port_num, uint8 pin_num, uint8 value){

    if((pin_num >= NUM_OF_PINS_PER_PORT) || (port_num >= NUM_OF_PORTS))
    {
        /* Do Nothing */
    }
    else{
        switch(port_num)
        {
        case PORTA_ID:

            if(value == LOGIC_HIGH){
                GPIO_PORTA_DATA_REG |= (1<<pin_num);
            }
            else{
                GPIO_PORTA_DATA_REG &= ~(1<<pin_num);
            }
            break;

        case PORTB_ID:

            if(value == LOGIC_HIGH){
                GPIO_PORTB_DATA_REG |= (1<<pin_num);
            }
            else{
                GPIO_PORTB_DATA_REG &= ~(1<<pin_num);
            }
            break;

        case PORTC_ID:

            /* From pin 0 to pin 3 in port c : JTAG pins please don't use them */
            if(pin_num <= 3){
                break;
            }

            if(value == LOGIC_HIGH){
                GPIO_PORTC_DATA_REG |= (1<<pin_num);
            }
            else{
                GPIO_PORTC_DATA_REG &= ~(1<<pin_num);
            }
            break;

        case PORTD_ID:

            if(value == LOGIC_HIGH){
                GPIO_PORTD_DATA_REG |= (1<<pin_num);
            }
            else{
                GPIO_PORTD_DATA_REG &= ~(1<<pin_num);
            }
            break;

        case PORTE_ID:

            if(value == LOGIC_HIGH){
                GPIO_PORTE_DATA_REG |= (1<<pin_num);
            }
            else{
                GPIO_PORTE_DATA_REG &= ~(1<<pin_num);
            }
            break;

        case PORTF_ID:

            if(value == LOGIC_HIGH){
                GPIO_PORTF_DATA_REG |= (1<<pin_num);
            }
            else{
                GPIO_PORTF_DATA_REG &= ~(1<<pin_num);
            }
            break;
        default :
            /*DO NOTHING*/

        }
    }
}

void GPIO_togglePin(GPIO_ports port_num, uint8 pin_num){

    if((pin_num >= NUM_OF_PINS_PER_PORT) || (port_num >= NUM_OF_PORTS))
    {
        /* Do Nothing */
    }
    else{
        switch(port_num)
        {
        case PORTA_ID:

            GPIO_PORTA_DATA_REG ^= (1<<pin_num);
            break;

        case PORTB_ID:

            GPIO_PORTB_DATA_REG ^= (1<<pin_num);
            break;

        case PORTC_ID:

            /* From pin 0 to pin 3 in port c : JTAG pins please don't use them */
            if(pin_num <= 3){
                break;
            }

            GPIO_PORTC_DATA_REG ^= (1<<pin_num);
            break;

        case PORTD_ID:

            GPIO_PORTD_DATA_REG ^= (1<<pin_num);
            break;

        case PORTE_ID:

            GPIO_PORTE_DATA_REG ^= (1<<pin_num);
            break;

        case PORTF_ID:

            GPIO_PORTF_DATA_REG ^= (1<<pin_num);
            break;
        default :
            /*DO NOTHING*/

        }
    }
}
uint8 GPIO_readPin(GPIO_ports port_num, uint8 pin_num){


    if((pin_num >= NUM_OF_PINS_PER_PORT) || (port_num >= NUM_OF_PORTS))
    {
        return 0;
    }
    switch(port_num){

    case PORTA_ID:
        return (GPIO_PORTA_DATA_REG & (1<<pin_num))>>pin_num;

    case PORTB_ID:
        return (GPIO_PORTB_DATA_REG & (1<<pin_num))>>pin_num;

    case PORTC_ID:

        /* From pin 0 to pin 3 in port c : JTAG pins please don't use them */
        if(pin_num <= 3){
            break;
        }

        return (GPIO_PORTC_DATA_REG & (1<<pin_num))>>pin_num;

    case PORTD_ID:
        return (GPIO_PORTD_DATA_REG & (1<<pin_num))>>pin_num;

    case PORTE_ID:
        return (GPIO_PORTE_DATA_REG & (1<<pin_num))>>pin_num;

    case PORTF_ID:
        return (GPIO_PORTF_DATA_REG & (1<<pin_num))>>pin_num;
    }

    return 0;
}


void GPIO_setupPortDirection(uint8 port_num, GPIO_PortDirectionType direction){

    if(port_num >= NUM_OF_PORTS){

        /* DO NOTHING */
    }
    else{

        SYSCTL_RCGCGPIO_REG |= (1<<port_num); // enable clock for PORT
        while((SYSCTL_PRGPIO_REG&(1<<port_num)) == 0){}; // make sure that the clock enabled for PORT

        switch(port_num){

        case PORTA_ID:

#if SIGNAL == DIGITAL
            GPIO_PORTA_DEN_REG = 0xFF;
            GPIO_PORTA_AMSEL_REG = 0; // Analog disable
#else
            GPIO_PORTA_DEN_REG = 0;
            GPIO_PORTA_AMSEL_REG = 0XFF; // Analog ENable
#endif
            GPIO_PORTA_AFSEL_REG = 0; // Alternative function disable
            GPIO_PORTA_DIR_REG = direction;
#if pulling == pull_up
            GPIO_PORTA_PUR_REG = ~direction;
#else
            GPIO_PORTA_PDR_REG = ~direction;
#endif
            break;

        case PORTB_ID:

#if SIGNAL == DIGITAL
            GPIO_PORTB_DEN_REG = 0xFF;
            GPIO_PORTB_AMSEL_REG = 0; // Analog disable
#else
            GPIO_PORTB_DEN_REG = 0;
            GPIO_PORTB_AMSEL_REG = 0XFF; // Analog ENable
#endif
            GPIO_PORTB_AFSEL_REG = 0; // Alternative function disable
            GPIO_PORTB_DIR_REG = direction;
#if pulling == pull_up
            GPIO_PORTB_PUR_REG = ~direction;
#else
            GPIO_PORTB_PDR_REG = ~direction;
#endif

            break;

        case PORTC_ID:

            if(direction == PORT_INPUT){

#if SIGNAL == DIGITAL
                GPIO_PORTC_DEN_REG = 0xFF;
                GPIO_PORTC_AMSEL_REG = 0; // Analog disable
#else
                GPIO_PORTC_DEN_REG = 0;
                GPIO_PORTC_AMSEL_REG = 0XFF; // Analog ENable
#endif
                GPIO_PORTC_AFSEL_REG &= 0x0F; // Alternative function disable
                GPIO_PORTC_DIR_REG   &= 0x0F;
#if pulling == pull_up
                GPIO_PORTC_PUR_REG = ~direction;
#else
                GPIO_PORTC_PDR_REG = ~direction;
#endif
            }
            else{

                GPIO_PORTC_DEN_REG   |= 0xF0;
                GPIO_PORTC_AMSEL_REG &= 0x0F; // Analog disable
                GPIO_PORTC_AFSEL_REG &= 0x0F; // Alternative function disable
                GPIO_PORTC_DIR_REG   |= 0xF0;
            }


            break;

        case PORTD_ID:

#if SIGNAL == DIGITAL
            GPIO_PORTD_DEN_REG = 0xFF;
            GPIO_PORTD_AMSEL_REG = 0; // Analog disable
#else
            GPIO_PORTD_DEN_REG = 0;
            GPIO_PORTD_AMSEL_REG = 0XFF; // Analog ENable
#endif
            GPIO_PORTD_AFSEL_REG = 0; // Alternative function disable
            GPIO_PORTD_DIR_REG = direction;
#if pulling == pull_up
            GPIO_PORTD_PUR_REG = ~direction;
#else
            GPIO_PORTD_PDR_REG = ~direction;
#endif

            break;

        case PORTE_ID:
#if SIGNAL == DIGITAL
            GPIO_PORTE_DEN_REG = 0xFF;
            GPIO_PORTE_AMSEL_REG = 0; // Analog disable
#else
            GPIO_PORTE_DEN_REG = 0;
            GPIO_PORTE_AMSEL_REG = 0XFF; // Analog ENable
#endif
            GPIO_PORTE_DEN_REG = 0xFF;
            GPIO_PORTE_AMSEL_REG = 0; // Analog disable
            GPIO_PORTE_AFSEL_REG = 0; // Alternative function disable
            GPIO_PORTE_DIR_REG = direction;
#if pulling == pull_up
            GPIO_PORTE_PUR_REG = ~direction;
#else
            GPIO_PORTE_PDR_REG = ~direction;
#endif
            break;

        case PORTF_ID:
#if SIGNAL == DIGITAL
            GPIO_PORTF_DEN_REG = 0xFF;
            GPIO_PORTF_AMSEL_REG = 0; // Analog disable
#else
            GPIO_PORTF_DEN_REG = 0;
            GPIO_PORTF_AMSEL_REG = 0XFF; // Analog ENable
#endif
            GPIO_PORTF_AFSEL_REG = 0; // Alternative function disable
            GPIO_PORTF_DIR_REG = direction;
#if pulling == pull_up
            GPIO_PORTF_PUR_REG = ~direction;
#else
            GPIO_PORTF_PDR_REG = ~direction;
#endif

            break;
        }
    }
}


void GPIO_writePort(uint8 port_num, uint8 value){

    if(port_num >= NUM_OF_PORTS)
    {
        /* Do Nothing */
    }
    else{

        switch(port_num){

        case PORTA_ID:
            GPIO_PORTA_DATA_REG = value;
            break;

        case PORTB_ID:
            GPIO_PORTB_DATA_REG = value;
            break;

        case PORTC_ID:
            GPIO_PORTC_DATA_REG = (GPIO_PORTC_DATA_REG & 0x0F) | (value & 0xF0);
            break;

        case PORTD_ID:
            GPIO_PORTD_DATA_REG = value;
            break;

        case PORTE_ID:
            GPIO_PORTE_DATA_REG = value;
            break;

        case PORTF_ID:
            GPIO_PORTF_DATA_REG = value;
            break;
        }
    }
}


uint8 GPIO_readPort(uint8 port_num){

    if(port_num >= NUM_OF_PORTS)
    {
        return 0;
    }
    else{

        switch(port_num){

        case PORTA_ID:
            return GPIO_PORTA_DATA_REG;

        case PORTB_ID:
            return GPIO_PORTB_DATA_REG;

        case PORTC_ID:
            return (GPIO_PORTC_DATA_REG & 0xF0);

        case PORTD_ID:
            return GPIO_PORTD_DATA_REG;

        case PORTE_ID:
            return GPIO_PORTE_DATA_REG;

        case PORTF_ID:
            return GPIO_PORTF_DATA_REG;
        }
    }
    return 0;
}

