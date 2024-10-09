/*
 * NVIC.c
 *
 *  Created on: Jul 26, 2024
 *      Author: Mina
 */

/*******************************************************************************
 *                                Inclusions                                   *
 *******************************************************************************/
#include "NVIC.h"
#include "tm4c123gh6pm_registers.h"

/*******************************************************************************
 *                         Public Functions Definitions                        *
 *******************************************************************************/

/*********************************************************************
 * Service Name: NVIC_EnableIRQ
 * Sync/Async: Synchronous
 * Reentrancy: reentrant
 * Parameters (in): IRQ_Num - Number of the IRQ from the target vector table
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Function to enable Interrupt request for specific IRQ
 **********************************************************************/
void NVIC_EnableIRQ(NVIC_IRQType IRQ_Num){

    if((IRQ_Num <= NUM_OF_FRIST_IRQ) || (IRQ_Num > NUM_OF_IRQ))
    {
        /*DO NOTHING*/
    }
    else
    {
        uint8 offset = IRQ_Num / NUM_BITS_PER_EN_REG;   /*Calculate the offset for the corresponding NVIC register*/
        volatile uint32 *address = &NVIC_EN0_REG + offset;
        uint32 bit = IRQ_Num % NUM_BITS_PER_EN_REG;     /* Set the irq bit in the corresponding enable register*/
        *address |= (1U << bit);       /* Enable NVIC Interrupt for GPIO PORTF by set bit number 30 in EN0 Register */
    }
}

/*********************************************************************
 * Service Name: NVIC_DisableIRQ
 * Sync/Async: Synchronous
 * Reentrancy: reentrant
 * Parameters (in): IRQ_Num - Number of the IRQ from the target vector table
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Function to Disable Interrupt request for specific IRQ
 **********************************************************************/
void NVIC_DisableIRQ(NVIC_IRQType IRQ_Num){

    if((IRQ_Num <= NUM_OF_FRIST_IRQ) || (IRQ_Num > NUM_OF_IRQ))
    {
        /*DO NOTHING*/
    }
    else
    {
        uint8 offset = IRQ_Num / NUM_BITS_PER_EN_REG;   /*Calculate the offset for the corresponding NVIC register*/
        volatile uint32 *address = &NVIC_DIS0_REG + offset;
        uint32 bit = IRQ_Num % NUM_BITS_PER_EN_REG;     /* Set the irq bit in the corresponding enable register*/
        *address |= (1U << bit);       /* Enable NVIC Interrupt for GPIO PORTF by set bit number 30 in EN0 Register */
    }
}

/*********************************************************************
 * Service Name: NVIC_NVIC_SetPriorityIRQ
 * Sync/Async: Synchronous
 * Reentrancy: reentrant
 * Parameters (in): IRQ_Num - Number of the IRQ from the target vector table ,
                    IRQ_Priority - Number of the priority needed (0-7)
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Function to set  Interrupt Priority for specific IRQ
 **********************************************************************/
void NVIC_SetPriorityIRQ(NVIC_IRQType IRQ_Num, NVIC_IRQPriorityType IRQ_Priority){

    if((IRQ_Num <= NUM_OF_FRIST_IRQ) || (IRQ_Num > NUM_OF_IRQ) ||  (IRQ_Priority > MAX_PRI) || (IRQ_Priority < MIN_PRI) )
    {
        /*DO NOTHING*/
    }
    else
    {
        uint8 offset = IRQ_Num / NUM_INTERRUPT_PER_PRLN_REG;   /*Calculate the offset for the corresponding NVIC register*/
        volatile uint32 *address = &NVIC_PRI0_REG + (offset*NUM_INTERRUPT_PER_PRLN_REG); /*Each register covers 4 interrupts*/
        uint8 position = ((IRQ_Num % NUM_INTERRUPT_PER_PRLN_REG) * NUM_BITS_PER_PRLN_REG_INTURRUPT)+ RESERVED_BITS_PRLN ;   /*Each interrupt uses 8 bits 3 for priority and 5 reserved*/
        *address = (*address & ~(HEX_NUM_PR_BITS <<position)) | ((IRQ_Priority & PRI_MASK)<<position);
    }
}

/*********************************************************************
 * Service Name: NVIC_EnableException
 * Sync/Async: Synchronous
 * Reentrancy: reentrant
 * Parameters (in): Exception_Num - Number of the Exception from the target vector table
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Function to enable Interrupt request for specific exception
 **********************************************************************/
void NVIC_EnableException(NVIC_ExceptionType Exception_Num){

    if((Exception_Num < NON_PROGRAMABLE_EXCEPTION) || (Exception_Num > 6))
    {
        /*DO NOTHING*/
    }
    else
    {
        NVIC_SYSTEM_SYSHNDCTRL |= (1<<(Exception_Num+12));
    }
}

/*********************************************************************
 * Service Name: NVIC_DisableException
 * Sync/Async: Synchronous
 * Reentrancy: reentrant
 * Parameters (in): Exception_Num - Number of the Exception_Num from the target vector table
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Function to disable Interrupt request for specific exception
 **********************************************************************/
void NVIC_DisableException(NVIC_ExceptionType Exception_Num){

    if((Exception_Num < NON_PROGRAMABLE_EXCEPTION) || (Exception_Num > 6))
    {
        /*DO NOTHING*/
    }
    else
    {
        NVIC_SYSTEM_SYSHNDCTRL &= ~(1<<(Exception_Num+12));
    }
}

/*********************************************************************
 * Service Name: NVIC_SetPriorityException
 * Sync/Async: Synchronous
 * Reentrancy: reentrant
 * Parameters (in):  Exception_Num - Number of the Exception from the target vector table ,
                     Exception_Priority - Number of the priority needed (0-7)
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Function to set  Interrupt Priority for specific exception
 **********************************************************************/
void NVIC_SetPriorityException(NVIC_ExceptionType Exception_Num, NVIC_ExceptionPriorityType Exception_Priority){
    if((Exception_Num < NUM_OF_FRIST_EXCEPTION) ||(Exception_Num > NUM_OF_EXCEPTIONS) ||  (Exception_Priority > MAX_PRI) || (Exception_Priority < MIN_PRI) )
    {
        /*DO NOTHING*/
    }
    else
    {
        if(Exception_Num <= NON_PROGRAMABLE_EXCEPTION  )
        {
            /*DO NOTHING*/
        }
        else{
            uint8 offset = Exception_Num / NUM_INTERRUPT_PER_PRLN_REG;   /*Calculate the offset for the corresponding NVIC register*/
            volatile uint32 *address = &NVIC_SYSTEM_PRI1_REG + (offset*NUM_INTERRUPT_PER_PRLN_REG)-NUM_INTERRUPT_PER_PRLN_REG; /*Each register covers 4 interrupts*/
            uint8 position = ((Exception_Num % NUM_INTERRUPT_PER_PRLN_REG) * NUM_BITS_PER_PRLN_REG_INTURRUPT)+ RESERVED_BITS_PRLN ;   /*Each interrupt uses 8 bits 3 for priority and 5 reserved*/
            *address = (*address & ~(HEX_NUM_PR_BITS <<position)) | ((Exception_Priority & PRI_MASK)<<position);
        }
    }
}

/************************************************************************************
 *                                 End of File                                      *
 ************************************************************************************/
