/******************************************************************************
 *
 * Module: NVIC
 *
 * File Name: NVIC.h
 *
 * Description: Header file for the ARM Cortex M4 NVIC driver
 *
 * Author: Mohamed Tarek (Edges For Training)
 *
 *******************************************************************************/

#ifndef NVIC_H_
#define NVIC_H_

/*******************************************************************************
 *                                Inclusions                                   *
 *******************************************************************************/
#include "std_types.h"

/*******************************************************************************
 *                           Preprocessor Definitions                          *
 *******************************************************************************/

#define MEM_FAULT_PRIORITY_MASK              0x000000E0
#define MEM_FAULT_PRIORITY_BITS_POS          5

#define BUS_FAULT_PRIORITY_MASK              0x0000E000
#define BUS_FAULT_PRIORITY_BITS_POS          13

#define USAGE_FAULT_PRIORITY_MASK            0x00E00000
#define USAGE_FAULT_PRIORITY_BITS_POS        21

#define SVC_PRIORITY_MASK                    0xE0000000
#define SVC_PRIORITY_BITS_POS                29

#define DEBUG_MONITOR_PRIORITY_MASK          0x000000E0
#define DEBUG_MONITOR_PRIORITY_BITS_POS      5

#define PENDSV_PRIORITY_MASK                 0x00E00000
#define PENDSV_PRIORITY_BITS_POS             21

#define SYSTICK_PRIORITY_MASK                0xE0000000
#define SYSTICK_PRIORITY_BITS_POS            29

#define MEM_FAULT_ENABLE_MASK                0x00010000
#define BUS_FAULT_ENABLE_MASK                0x00020000
#define USAGE_FAULT_ENABLE_MASK              0x00040000

#define NUM_BITS_PER_EN_REG                  32

#define NON_PROGRAMABLE_EXCEPTION            3
#define NUM_OF_EXCEPTIONS                    15
#define NUM_OF_FRIST_EXCEPTION               1

#define NUM_OF_IRQ                           138
#define NUM_OF_FRIST_IRQ                     0

#define MAX_PRI                              7
#define MIN_PRI                              0
#define PRI_MASK                             0x07

#define RESERVED_BITS_PRLN                   5
#define HEX_NUM_PR_BITS                      0X00000007
#define NUM_INTERRUPT_PER_PRLN_REG           4
#define NUM_BITS_PER_PRLN_REG_INTURRUPT      8

/*******************************************************************************
*                           Preprocessor macros                                *
*******************************************************************************/

/* Enable Exceptions ... This Macro enable IRQ interrupts, Programmable Systems Exceptions and Faults by clearing the I-bit in the PRIMASK. */
#define Enable_Exceptions()    __asm(" CPSIE I ")

/* Disable Exceptions ... This Macro disable IRQ interrupts, Programmable Systems Exceptions and Faults by setting the I-bit in the PRIMASK. */
#define Disable_Exceptions()   __asm(" CPSID I ")

/* Enable Faults ... This Macro enable Faults by clearing the F-bit in the FAULTMASK */
#define Enable_Faults()        __asm(" CPSIE F ")

/* Disable Faults ... This Macro disable Faults by setting the F-bit in the FAULTMASK */
#define Disable_Faults()       __asm(" CPSID F ")

/* Go to low power mode while waiting for the next interrupt */
#define Wait_For_Interrupt()   __asm(" WFI ")

/*******************************************************************************
 *                           Data Types Declarations                           *
 *******************************************************************************/
typedef uint8 NVIC_IRQType;

typedef uint8 NVIC_IRQPriorityType;

typedef enum
{
    IRQ_GPIO_PORTF =30
}NVIC_IRQ_Type;

typedef enum
{
    EXCEPTION_RESET_TYPE=1,
    EXCEPTION_NMI_TYPE=2,
    EXCEPTION_HARD_FAULT_TYPE=3,
    EXCEPTION_MEM_FAULT_TYPE=4,
    EXCEPTION_BUS_FAULT_TYPE=5,
    EXCEPTION_USAGE_FAULT_TYPE=6,
    EXCEPTION_SVC_TYPE=11,
    EXCEPTION_DEBUG_MONITOR_TYPE=12,
    EXCEPTION_PEND_SV_TYPE =14,
    EXCEPTION_SYSTICK_TYPE =15
}NVIC_ExceptionType;

typedef uint8 NVIC_ExceptionPriorityType;

/*******************************************************************************
 *                            Functions Prototypes                             *
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
void NVIC_EnableIRQ(NVIC_IRQType IRQ_Num);

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
void NVIC_DisableIRQ(NVIC_IRQType IRQ_Num);

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
void NVIC_SetPriorityIRQ(NVIC_IRQType IRQ_Num, NVIC_IRQPriorityType IRQ_Priority);

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
void NVIC_EnableException(NVIC_ExceptionType Exception_Num);

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
void NVIC_DisableException(NVIC_ExceptionType Exception_Num);

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
void NVIC_SetPriorityException(NVIC_ExceptionType Exception_Num, NVIC_ExceptionPriorityType Exception_Priority);

/************************************************************************************
 *                                 End of File                                      *
 ************************************************************************************/

#endif /* NVIC_H_ */
