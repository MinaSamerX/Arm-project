/*
 * ext_interrupt.c
 *
 *  Created on: Jul 26, 2024
 *      Author: Mina
 */

#include "ext_interrupt.h"
#include "tm4c123gh6pm_registers.h"


/***************************************************************************
 *                            Global variables                             *
 ***************************************************************************/

static volatile void (*g_callBackPtr_A) (void) = NULL_PTR;
static volatile void (*g_callBackPtr_B) (void) = NULL_PTR;
static volatile void (*g_callBackPtr_C) (void) = NULL_PTR;
static volatile void (*g_callBackPtr_D) (void) = NULL_PTR;
static volatile void (*g_callBackPtr_E) (void) = NULL_PTR;
static volatile void (*g_callBackPtr_F) (void) = NULL_PTR;



/***************************************************************************
 *                          HANDLER Functions                              *
 ***************************************************************************/

/* GPIO PORTA External Interrupt - ISR */
void GPIOPortA_Handler(void)
{
    (*g_callBackPtr_A)();  /*call the handler function*/
    GPIO_PORTA_ICR_REG = 0x7F;       /* Clear Trigger flag (Interrupt Flag) */
}


/* GPIO PORTB External Interrupt - ISR */
void GPIOPortB_Handler(void)
{
    (*g_callBackPtr_B)();  /*call the handler function*/
    GPIO_PORTB_ICR_REG = 0x7F;       /* Clear Trigger flag (Interrupt Flag) */
}

/* GPIO PORTC External Interrupt - ISR */
void GPIOPortC_Handler(void)
{
    (*g_callBackPtr_C)();  /*call the handler function*/
    GPIO_PORTC_ICR_REG = 0x7F;       /* Clear Trigger flag (Interrupt Flag) */
}


/* GPIO PORTD External Interrupt - ISR */
void GPIOPortD_Handler(void)
{
    (*g_callBackPtr_D)();  /*call the handler function*/
    GPIO_PORTD_ICR_REG = 0x7F;       /* Clear Trigger flag (Interrupt Flag) */
}

/* GPIO PORTE External Interrupt - ISR */
void GPIOPortE_Handler(void)
{
    (*g_callBackPtr_E)();  /*call the handler function*/
    GPIO_PORTE_ICR_REG = 0x7F;       /* Clear Trigger flag (Interrupt Flag) */
}


/* GPIO PORTF External Interrupt - ISR */
void GPIOPortF_Handler(void)
{
    (*g_callBackPtr_F)();  /*call the handler function*/
    GPIO_PORTF_ICR_REG = 0x7F;       /* Clear Trigger flag (Interrupt Flag) */
}

/***************************************************************************
 *                          Functions definition                           *
 ***************************************************************************/

void EXT_interrupte_Init(GPIO_port port_num, uint8 pin_num)
{
    if((pin_num >= NUM_OF_PINS_PER_PORT) || (port_num >= NUM_OF_PORTS))
    {
        /* Do Nothing */
    }
    else
    {
        switch(port_num){
        case PORTA_ID:
            GPIO_PORTA_IS_REG    &= ~(1<<pin_num);      /* detect edges */
            GPIO_PORTA_IBE_REG   &= ~(1<<pin_num);      /*  will detect a certain edge */
            GPIO_PORTA_IEV_REG   &= ~(1<<pin_num);      /*  will detect a falling edge */
            GPIO_PORTA_ICR_REG   |= (1<<pin_num);       /* Clear Trigger flag (Interrupt Flag) */
            GPIO_PORTA_IM_REG    |= (1<<pin_num);       /* Enable Interrupt on pin */
            break;
        case PORTB_ID:
            GPIO_PORTB_IS_REG    &= ~(1<<pin_num);      /* detect edges */
            GPIO_PORTB_IBE_REG   &= ~(1<<pin_num);      /*  will detect a certain edge */
            GPIO_PORTB_IEV_REG   &= ~(1<<pin_num);      /*  will detect a falling edge */
            GPIO_PORTB_ICR_REG   |= (1<<pin_num);       /* Clear Trigger flag (Interrupt Flag) */
            GPIO_PORTB_IM_REG    |= (1<<pin_num);       /* Enable Interrupt on pin */
            break;
        case PORTC_ID:
            GPIO_PORTC_IS_REG    &= ~(1<<pin_num);      /* detect edges */
            GPIO_PORTC_IBE_REG   &= ~(1<<pin_num);      /*  will detect a certain edge */
            GPIO_PORTC_IEV_REG   &= ~(1<<pin_num);      /*  will detect a falling edge */
            GPIO_PORTC_ICR_REG   |= (1<<pin_num);       /* Clear Trigger flag (Interrupt Flag) */
            GPIO_PORTC_IM_REG    |= (1<<pin_num);       /* Enable Interrupt on pin */
            break;
        case PORTD_ID:
            GPIO_PORTD_IS_REG    &= ~(1<<pin_num);      /* detect edges */
            GPIO_PORTD_IBE_REG   &= ~(1<<pin_num);      /*  will detect a certain edge */
            GPIO_PORTD_IEV_REG   &= ~(1<<pin_num);      /*  will detect a falling edge */
            GPIO_PORTD_ICR_REG   |= (1<<pin_num);       /* Clear Trigger flag (Interrupt Flag) */
            GPIO_PORTD_IM_REG    |= (1<<pin_num);       /* Enable Interrupt on pin */
            break;
        case PORTE_ID:
            GPIO_PORTE_IS_REG    &= ~(1<<pin_num);      /* detect edges */
            GPIO_PORTE_IBE_REG   &= ~(1<<pin_num);      /*  will detect a certain edge */
            GPIO_PORTE_IEV_REG   &= ~(1<<pin_num);      /*  will detect a falling edge */
            GPIO_PORTE_ICR_REG   |= (1<<pin_num);       /* Clear Trigger flag (Interrupt Flag) */
            GPIO_PORTE_IM_REG    |= (1<<pin_num);       /* Enable Interrupt on pin */
            break;
        case PORTF_ID:
            GPIO_PORTF_IS_REG    &= ~(1<<pin_num);      /* detect edges */
            GPIO_PORTF_IBE_REG   &= ~(1<<pin_num);      /*  will detect a certain edge */
            GPIO_PORTF_IEV_REG   &= ~(1<<pin_num);      /*  will detect a falling edge */
            GPIO_PORTF_ICR_REG   |= (1<<pin_num);       /* Clear Trigger flag (Interrupt Flag) */
            GPIO_PORTF_IM_REG    |= (1<<pin_num);       /* Enable Interrupt on pin */
            break;
        default:
            /*DO NOTHING */
        }
    }
}



void EXT_interrupte_SetCallBack_A(volatile void (*Ptr) (void)){

    g_callBackPtr_A = Ptr;
}

void EXT_interrupte_SetCallBack_B(volatile void (*Ptr) (void)){

    g_callBackPtr_B = Ptr;
}

void EXT_interrupte_SetCallBack_C(volatile void (*Ptr) (void)){

    g_callBackPtr_C = Ptr;
}

void EXT_interrupte_SetCallBack_D(volatile void (*Ptr) (void)){

    g_callBackPtr_D = Ptr;
}

void EXT_interrupte_SetCallBack_E(volatile void (*Ptr) (void)){

    g_callBackPtr_E = Ptr;
}

void EXT_interrupte_SetCallBack_F(volatile void (*Ptr) (void)){

    g_callBackPtr_F = Ptr;
}

