/*
 * SYSTICK.c
 *
 *  Created on: Jul 27, 2024
 *      Author: Mina
 */

/*******************************************************************************
 *                                Inclusions                                   *
 *******************************************************************************/

#include"SYSTICK.h"
#include "tm4c123gh6pm_registers.h"

/***************************************************************************
 *                            Global variables                             *
 ***************************************************************************/

static volatile void (*g_callBackPtr) (void) = NULL_PTR;

static volatile uint16 g_remainingTime = 0;

static volatile uint8 flag = 0;

/***************************************************************************
 *                          HANDLER Functions                              *
 ***************************************************************************/

/*********************************************************************
 * Service Name: SysTick_Handler
 * Sync/Async: Synchronous
 * Reentrancy: reentrant
 * Parameters (in): None
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Handler for SysTick interrupt use to call the call-back function.
 ***********************************************************************/
void SysTick_Handler(void) {
    if(flag == TRUE)
    {
        if (g_remainingTime > MAX_RELOAD){
            g_remainingTime= g_remainingTime -MAX_RELOAD;
            SYSTICK_RELOAD_REG = (MAX_RELOAD - 1);

        }
        else
        {
            SYSTICK_RELOAD_REG = (g_remainingTime - 1);
            flag=0;
        }
    }
    else
    {
        (*g_callBackPtr)();  /*call the handler function*/
    }
}
/*******************************************************************************
 *                         Public Functions Definitions                        *
 *******************************************************************************/

/*********************************************************************
 * Service Name: SysTick_Init
 * Sync/Async: Synchronous
 * Reentrancy: reentrant
 * Parameters (in): a_TimeInMilliSeconds - Time needed to count
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Initialize the SysTick timer with the specified time in milliseconds using interrupts.
 * This function is used to setup the timer to generate periodic interrupts every specified time in milliseconds.
 **********************************************************************/
void SysTick_Init(uint16 a_TimeInMilliSeconds) {
    SYSTICK_CTRL_REG    = 0;              /* Disable the SysTick Timer by Clear the ENABLE Bit */
    SYSTICK_CURRENT_REG = 0;              /* Clear the Current Register value */

    SYSTICK_CTRL_REG |= (1<<2);           /* Use system clock as clock source */
    SYSTICK_CTRL_REG |= (1<<1);           /* Enable interrupt for sysTick timer */
    SYSTICK_CTRL_REG &= ~(1<<0);          /* Disable counter (pending to be enabled for accuracy) */


    uint32 reload = CPU_FREQ *a_TimeInMilliSeconds * MILLI_SEC;
    if (reload > MAX_RELOAD)
    {
        g_remainingTime  = reload-MAX_RELOAD;
        SYSTICK_RELOAD_REG = (MAX_RELOAD - 1);
        flag = 1;
    }
    else
    {
        SYSTICK_RELOAD_REG = (reload - 1);
    }
}

/*********************************************************************
 * Service Name: SysTick_StartBusyWait
 * Sync/Async: Synchronous
 * Reentrancy: reentrant
 * Parameters (in): a_TimeInMilliSeconds - Time needed to count
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Initialize the SysTick timer with the specified time in milliseconds using polling or busy-wait technique.
 * The function should exit when the time is elapsed and stops the timer at the end.
 **********************************************************************/
void SysTick_StartBusyWait(uint16 a_TimeInMilliSeconds){

    SYSTICK_CTRL_REG    = 0;              /* Disable the SysTick Timer by Clear the ENABLE Bit */
    SYSTICK_CURRENT_REG = 0;              /* Clear the Current Register value */

    SYSTICK_CTRL_REG |= (1<<2);           /* Use system clock as clock source */
    SYSTICK_CTRL_REG &= ~(1<<1);          /* Disable interrupt for sysTick timer */

    SYSTICK_CTRL_REG &= ~(1<<0);          /* Disable counter (pending to be enabled for accuracy) */

    uint32 reload = CPU_FREQ *a_TimeInMilliSeconds * MILLI_SEC;
    if (reload > MAX_RELOAD)
    {
        g_remainingTime  = reload-MAX_RELOAD;
        while(g_remainingTime >= MAX_RELOAD){
            g_remainingTime= g_remainingTime -MAX_RELOAD;
            SYSTICK_RELOAD_REG = (MAX_RELOAD - 1);
            SYSTICK_CTRL_REG |= 1;                 /* Enable sysTick timer */
            while(!(SYSTICK_CTRL_REG & (1<<16)));  /* Reading the counter flag that means the timer finished */
        }
    }
    else
    {
        SYSTICK_RELOAD_REG = (reload - 1);
        SYSTICK_CTRL_REG |= 1;                 /* Enable sysTick timer */
        while(!(SYSTICK_CTRL_REG & (1<<16)));  /* Reading the counter flag that means the timer finished */
    }

    SYSTICK_CTRL_REG &= ~(1<<0);           /* Disable counter */
}

/*********************************************************************
 * Service Name: SysTick_SetCallBack
 * Sync/Async: Synchronous
 * Reentrancy: reentrant
 * Parameters (in): Ptr2Func - To pass the function name which you want ISR call
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Function to setup the SysTick Timer call back to be executed in SysTick Handler.
 ***********************************************************************/
void SysTick_SetCallBack(volatile void (*Ptr2Func) (void)){

    g_callBackPtr = Ptr2Func;  /* Assign local pointer to global one*/

}

/*********************************************************************
 * Service Name: SysTick_Stop
 * Sync/Async: Synchronous
 * Reentrancy: reentrant
 * Parameters (in): None
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Stop the SysTick timer.
 ***********************************************************************/
void SysTick_Stop(void){

    /* Disable counter */
    SYSTICK_CTRL_REG &= ~(1<<0);
}

/*********************************************************************
 * Service Name: SysTick_Start
 * Sync/Async: Synchronous
 * Reentrancy: reentrant
 * Parameters (in): None
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Start/Resume the SysTick timer.
 ***********************************************************************/
void SysTick_Start(void){

    /* Enable sysTick timer */
    SYSTICK_CTRL_REG |= 1;
}

/*********************************************************************
 * Service Name: SysTick_DeInit
 * Sync/Async: Synchronous
 * Reentrancy: reentrant
 * Parameters (in): None
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Function to De-initialize the SysTick Timer.
 ***********************************************************************/
void SysTick_DeInit(void){

    SYSTICK_RELOAD_REG = 0;
    SYSTICK_CURRENT_REG = 0;
    SYSTICK_CTRL_REG = 0;
}

/************************************************************************************
 *                                 End of File                                      *
 ************************************************************************************/
