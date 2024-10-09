#include "SYSTICK.h"
#include "NVIC.h"
#include "tiva_LEDS.h"
#include "tiva_SW.h"
#include "ext_interrupt.h"
#include "delay.h"

#define GPIO_PORTF_IRQ_NUM                30
#define GPIO_PORTF_INTERRUPT_PRIORITY     2
#define SYSTICK_INTERRUPT_PRIORITY        1

/* Global variable to count time in seconds */
volatile uint8 g_Counter = 0;

void GPIOPortF_PortFCALLBACK(void)
{
    SysTick_Stop();
    set_oneLED(ALL);
    Delay_MS(5000);
    SysTick_Start();
}
void SysTick_CallBackFunc(void)
{
    g_Counter++;

    switch(g_Counter)
    {
    case 1:
       set_oneLED(RED); /* Turn on the Red LED and disable the others */
        break;
    case 2:
        set_oneLED(BLUE); /* Turn on the Blue LED and disable the others */
        break;
    case 3:
        set_oneLED(GREEN); /* Turn on the Green LED and disable the others */
        g_Counter = 0;
        break;
    }
}

int main(void)
{

    /* Initialize the SW2(PF0) as GPIO Pin and activate external interrupt with falling edge */
    SW_init(SW2);
    EXT_interrupte_Init(PORTF_ID,SW2);
    NVIC_EnableIRQ(GPIO_PORTF_IRQ_NUM);
    NVIC_SetPriorityIRQ(GPIO_PORTF_IRQ_NUM,GPIO_PORTF_INTERRUPT_PRIORITY);
    EXT_interrupte_SetCallBack_F(GPIOPortF_PortFCALLBACK);

    /* Initialize the LEDs as GPIO Pins */
    LED_init(ALL);

    /* Start SysTick Timer to generate interrupt every 1 second */
    SysTick_Init(1000);
    NVIC_SetPriorityException(EXCEPTION_SYSTICK_TYPE,SYSTICK_INTERRUPT_PRIORITY);
    SysTick_SetCallBack(SysTick_CallBackFunc);

    /* Enable Interrupts, Exceptions and Faults */
    Enable_Exceptions();
    Enable_Faults();

    while(1)
    {

    }
}
