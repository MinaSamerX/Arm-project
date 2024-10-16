/*
 * SYSTICK.H
 *
 *  Created on: Jul 27, 2024
 *      Author: Mina
 */

#ifndef SYSTICK_H_
#define SYSTICK_H_

/******************************************************************************
*                                Inclusions                                   *
*******************************************************************************/

#include "std_types.h"

/******************************************************************************
*                           Preprocessor Definitions                          *
*******************************************************************************/

#define CPU_FREQ    16000000u
#define MILLI_SEC    0.001f
#define MAX_RELOAD  16000000u


/*******************************************************************************************************
*                                        Functions prototype                                           *
********************************************************************************************************/

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
void SysTick_Init(uint16 a_TimeInMilliSeconds);

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
void SysTick_StartBusyWait(uint16 a_TimeInMilliSeconds);

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
void SysTick_SetCallBack(volatile void (*Ptr2Func) (void));

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
void SysTick_Stop(void);

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
void SysTick_Start(void);

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
void SysTick_DeInit(void);

/************************************************************************************
 *                                 End of File                                      *
 ************************************************************************************/

#endif /* SYSTICK_H_ */
