#include "SYSTICK.h"
#include "NVIC.h"
#include "tiva_LEDS.h"
#include "tm4c123gh6pm_registers.h"
#include <assert.h>

#define MEM_FAULT_PRIORITY                  1
#define BUS_FAULT_PRIORITY                  2
#define USAGE_FAULT_PRIORITY                3
#define SVC_EXCEPTION_PRIORITY              4
#define DEBUG_MONITOR_EXCEPTION_PRIORITY    5
#define PENDSV_EXCEPTION_PRIORITY           6
#define SYSTICK_EXCEPTION_PRIORITY          7



void Test_Exceptions_Settings(void)
{
    /* Enable Memory Management Fault and Setup its priority */
    NVIC_EnableException(EXCEPTION_MEM_FAULT_TYPE);
    NVIC_SetPriorityException(EXCEPTION_MEM_FAULT_TYPE,MEM_FAULT_PRIORITY);

    assert(NVIC_SYSTEM_SYSHNDCTRL & MEM_FAULT_ENABLE_MASK);
    assert(((NVIC_SYSTEM_PRI1_REG & MEM_FAULT_PRIORITY_MASK) >> MEM_FAULT_PRIORITY_BITS_POS) == MEM_FAULT_PRIORITY);

    /* Disable Memory Management Fault */
    NVIC_DisableException(EXCEPTION_MEM_FAULT_TYPE);
    assert(!(NVIC_SYSTEM_SYSHNDCTRL & MEM_FAULT_ENABLE_MASK));

    /* Enable Bus Fault and Setup its priority */
    NVIC_EnableException(EXCEPTION_BUS_FAULT_TYPE);
    NVIC_SetPriorityException(EXCEPTION_BUS_FAULT_TYPE,BUS_FAULT_PRIORITY);

    assert(NVIC_SYSTEM_SYSHNDCTRL & BUS_FAULT_ENABLE_MASK);
    assert(((NVIC_SYSTEM_PRI1_REG & BUS_FAULT_PRIORITY_MASK) >> BUS_FAULT_PRIORITY_BITS_POS) == BUS_FAULT_PRIORITY);

    /* Disable Bus Fault */
    NVIC_DisableException(EXCEPTION_BUS_FAULT_TYPE);
    assert(!(NVIC_SYSTEM_SYSHNDCTRL & BUS_FAULT_ENABLE_MASK));

    /* Enable Usage Fault and Setup its priority */
    NVIC_EnableException(EXCEPTION_USAGE_FAULT_TYPE);
    NVIC_SetPriorityException(EXCEPTION_USAGE_FAULT_TYPE,USAGE_FAULT_PRIORITY);

    assert(NVIC_SYSTEM_SYSHNDCTRL & USAGE_FAULT_ENABLE_MASK);
    assert(((NVIC_SYSTEM_PRI1_REG & USAGE_FAULT_PRIORITY_MASK) >> USAGE_FAULT_PRIORITY_BITS_POS) == USAGE_FAULT_PRIORITY);

    /* Disable Usage Fault */
    NVIC_DisableException(EXCEPTION_USAGE_FAULT_TYPE);
    assert(!(NVIC_SYSTEM_SYSHNDCTRL & USAGE_FAULT_ENABLE_MASK));

    /* Setup priority for SVC Exception */
    NVIC_SetPriorityException(EXCEPTION_SVC_TYPE,SVC_EXCEPTION_PRIORITY);
    assert(((NVIC_SYSTEM_PRI2_REG & SVC_PRIORITY_MASK) >> SVC_PRIORITY_BITS_POS) == SVC_EXCEPTION_PRIORITY);

    /* Setup priority for SVC Exception */
    NVIC_SetPriorityException(EXCEPTION_DEBUG_MONITOR_TYPE,DEBUG_MONITOR_EXCEPTION_PRIORITY);
    assert(((NVIC_SYSTEM_PRI3_REG & DEBUG_MONITOR_PRIORITY_MASK) >> DEBUG_MONITOR_PRIORITY_BITS_POS) == DEBUG_MONITOR_EXCEPTION_PRIORITY);

    /* Setup priority for PendSV Exception */
    NVIC_SetPriorityException(EXCEPTION_PEND_SV_TYPE,PENDSV_EXCEPTION_PRIORITY);
    assert(((NVIC_SYSTEM_PRI3_REG & PENDSV_PRIORITY_MASK) >> PENDSV_PRIORITY_BITS_POS) == PENDSV_EXCEPTION_PRIORITY);

    /* Setup priority for SysTick Exception */
    NVIC_SetPriorityException(EXCEPTION_SYSTICK_TYPE,SYSTICK_EXCEPTION_PRIORITY);
    assert(((NVIC_SYSTEM_PRI3_REG & SYSTICK_PRIORITY_MASK) >> SYSTICK_PRIORITY_BITS_POS) == SYSTICK_EXCEPTION_PRIORITY);
}

int main(void)
{
    /* Initialize the LEDs as GPIO Pins */
    LED_init(ALL);

    /* Enable Interrupts, Exceptions and Faults */
    Enable_Exceptions();
    Enable_Faults();

    /* Test all System and Fault Exceptions settings */
    Test_Exceptions_Settings();

    while(1)
    {
        set_oneLED(RED); /* Turn on the Red LED and disable the others */
        SysTick_StartBusyWait(1000); /* Wait 1 second using SysTick Timer */
        set_oneLED(BLUE); /* Turn on the Blue LED and disable the others */
        SysTick_StartBusyWait(1000); /* Wait 1 second using SysTick Timer */
        set_oneLED(GREEN); /* Turn on the Green LED and disable the others */
        SysTick_StartBusyWait(1000); /* Wait 1 second using SysTick Timer */
    }
}
