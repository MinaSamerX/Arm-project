/*
 * tiva_LEDS.c
 *
 *  Created on: Jul 13, 2024
 *      Author: Mina
 */

#include "tiva_LEDS.h"
#include"gpio.h"
#ifdef DELAY
#include"delay.h"
#endif
#ifdef SYSTICK
#include "systick_timer.h"
#endif

void LED_init( LED_color color)
{
    if(color < DB_LED){
        GPIO_setupPinDirection(LED_PORT,color,PIN_OUTPUT);
        GPIO_writePin(LED_PORT,color,LOGIC_LOW); /* LED OFF as default*/
    }
    else if ((color >= DB_LED) && (color <= ALL)){
        switch(color){
        case MAGENTA :
            GPIO_setupPinDirection(LED_PORT,RED,PIN_OUTPUT);
            GPIO_setupPinDirection(LED_PORT,BLUE,PIN_OUTPUT);
            GPIO_writePin(LED_PORT,RED,LOGIC_LOW); /* LED OFF as default*/
            GPIO_writePin(LED_PORT,BLUE,LOGIC_LOW); /* LED OFF as default*/
            break;
        case ORANGE :
            GPIO_setupPinDirection(LED_PORT,RED,PIN_OUTPUT);
            GPIO_setupPinDirection(LED_PORT,GREEN,PIN_OUTPUT);
            GPIO_writePin(LED_PORT,RED,LOGIC_LOW); /* LED OFF as default*/
            GPIO_writePin(LED_PORT,GREEN,LOGIC_LOW); /* LED OFF as default*/
            break;
        case CYAN :
            GPIO_setupPinDirection(LED_PORT,BLUE,PIN_OUTPUT);
            GPIO_setupPinDirection(LED_PORT,GREEN,PIN_OUTPUT);
            GPIO_writePin(LED_PORT,BLUE,LOGIC_LOW); /* LED OFF as default*/
            GPIO_writePin(LED_PORT,GREEN,LOGIC_LOW); /* LED OFF as default*/
            break;
        case WHITE :
            GPIO_setupPinDirection(LED_PORT,RED,PIN_OUTPUT);
            GPIO_setupPinDirection(LED_PORT,BLUE,PIN_OUTPUT);
            GPIO_setupPinDirection(LED_PORT,GREEN,PIN_OUTPUT);
            GPIO_writePin(LED_PORT,RED,LOGIC_LOW); /* LED OFF as default*/
            GPIO_writePin(LED_PORT,BLUE,LOGIC_LOW); /* LED OFF as default*/
            GPIO_writePin(LED_PORT,GREEN,LOGIC_LOW); /* LED OFF as default*/
            break;
        default :
            /*DO NOTHING*/
        }
    }
    else{
        /*DO NOTHING*/
    }
}

void LED_status ( LED_color color , LED_cond status)
{
    switch(status){

    case ON :
        if(color < DB_LED){
            GPIO_writePin(LED_PORT,color,LOGIC_HIGH); /* LED OFF */
        }
        else if ((color >= DB_LED) && (color <= ALL)){
            switch(color){
            case MAGENTA :
                GPIO_writePin(LED_PORT,RED,LOGIC_HIGH); /* LED OFF as default*/
                GPIO_writePin(LED_PORT,BLUE,LOGIC_HIGH); /* LED OFF as default*/
                break;
            case ORANGE :
                GPIO_writePin(LED_PORT,RED,LOGIC_HIGH); /* LED OFF as default*/
                GPIO_writePin(LED_PORT,GREEN,LOGIC_HIGH); /* LED OFF as default*/
                break;
            case CYAN :
                GPIO_writePin(LED_PORT,BLUE,LOGIC_HIGH); /* LED OFF as default*/
                GPIO_writePin(LED_PORT,GREEN,LOGIC_HIGH); /* LED OFF as default*/
                break;
            case WHITE :
                GPIO_writePin(LED_PORT,RED,LOGIC_HIGH); /* LED OFF as default*/
                GPIO_writePin(LED_PORT,BLUE,LOGIC_HIGH); /* LED OFF as default*/
                GPIO_writePin(LED_PORT,GREEN,LOGIC_HIGH); /* LED OFF as default*/
                break;
            default :
                /*DO NOTHING*/
            }
        }
        else{
            /*DO NOTHING*/
        }
        break;

    case OFF:
        if(color < DB_LED){
            GPIO_writePin(LED_PORT,color,LOGIC_LOW); /* LED OFF */
        }
        else if ((color >= DB_LED) && (color <= ALL)){
            switch(color){
            case MAGENTA :
                GPIO_writePin(LED_PORT,RED,LOGIC_LOW); /* LED OFF as default*/
                GPIO_writePin(LED_PORT,BLUE,LOGIC_LOW); /* LED OFF as default*/
                break;
            case ORANGE :
                GPIO_writePin(LED_PORT,RED,LOGIC_LOW); /* LED OFF as default*/
                GPIO_writePin(LED_PORT,GREEN,LOGIC_LOW); /* LED OFF as default*/
                break;
            case CYAN :
                GPIO_writePin(LED_PORT,BLUE,LOGIC_LOW); /* LED OFF as default*/
                GPIO_writePin(LED_PORT,GREEN,LOGIC_LOW); /* LED OFF as default*/
                break;
            case WHITE :
                GPIO_writePin(LED_PORT,RED,LOGIC_LOW); /* LED OFF as default*/
                GPIO_writePin(LED_PORT,BLUE,LOGIC_LOW); /* LED OFF as default*/
                GPIO_writePin(LED_PORT,GREEN,LOGIC_LOW); /* LED OFF as default*/
                break;
            default :
                /*DO NOTHING*/
            }
        }
        else{
            /*DO NOTHING*/
        }
        break;
    default :
        /*DO NOTHING*/
    }
}

void set_oneLED(LED_color color){
    switch(color){
    case RED:
        PF1_PF2_PF3 = 0x02;
        break;
    case BLUE:
        PF1_PF2_PF3 = 0x04;
        break;
    case GREEN:
        PF1_PF2_PF3 = 0x08;
        break;
    case MAGENTA :
        PF1_PF2_PF3 = 0x06;
        break;
    case ORANGE :
        PF1_PF2_PF3 = 0x0A;
        break;
    case CYAN :
        PF1_PF2_PF3 = 0x0C;
        break;
    case WHITE :
        PF1_PF2_PF3 = 0x0E;
        break;
    default :
        /*DO NOTHING*/
    }
}

void toggle_LED(LED_color color){
    if(color < DB_LED){
        GPIO_togglePin(LED_PORT,color);
    }
    else if ((color >= DB_LED) && (color <= ALL)){
        switch(color){
        case MAGENTA :
            GPIO_togglePin(LED_PORT,RED);
            GPIO_togglePin(LED_PORT,BLUE);
            break;
        case ORANGE :
            GPIO_togglePin(LED_PORT,RED);
            GPIO_togglePin(LED_PORT,GREEN);
            break;
        case CYAN :
            GPIO_togglePin(LED_PORT,BLUE);
            GPIO_togglePin(LED_PORT,GREEN);
            break;
        case WHITE :
            GPIO_togglePin(LED_PORT,RED);
            GPIO_togglePin(LED_PORT,BLUE);
            GPIO_togglePin(LED_PORT,GREEN);
            break;
        default :
            /*DO NOTHING*/
        }
    }
    else{
        /*DO NOTHING*/
    }
}

void rolling_init(void){
    GPIO_setupPinDirection(LED_PORT,RED,PIN_OUTPUT);
    GPIO_setupPinDirection(LED_PORT,BLUE,PIN_OUTPUT);
    GPIO_setupPinDirection(LED_PORT,GREEN,PIN_OUTPUT);
}

#ifdef DELAY
void LED_rolling_delay(uint64 D){
    /* Access each pin individually using the Bit Band feature */
    /* Turn on the Red LED */
    /* Turn off the Blue LED */
    /* Turn off the Green LED */
    PF1_PF2_PF3 = 0x02;
    Delay_MS(D);

    /* Access each pin individually using the Bit Band feature */
    /* Turn off the Red LED */
    /* Turn on the Blue LED */
    /* Turn off the Green LED */
    PF1_PF2_PF3 = 0x04;
    Delay_MS(D);

    /* Access each pin individually using the Bit Band feature */
    /* Turn off the Red LED */
    /* Turn off the Blue LED */
    /* Turn on the Green LED */
    PF1_PF2_PF3 = 0x08;
    Delay_MS(D);

    /* Access each pin individually using the Bit Band feature */
    /* Turn on the Red LED */
    /* Turn on the Blue LED */
    /* Turn off the Green LED */
    PF1_PF2_PF3 = 0x06;
    Delay_MS(D);

    /* Access each pin individually using the Bit Band feature */
    /* Turn on the Red LED */
    /* Turn off the Blue LED */
    /* Turn on the Green LED */
    PF1_PF2_PF3 = 0x0A;
    Delay_MS(D);

    /* Access each pin individually using the Bit Band feature */
    /* Turn off the Red LED */
    /* Turn on the Blue LED */
    /* Turn on the Green LED */
    PF1_PF2_PF3 = 0x0C;
    Delay_MS(D);

    /* Access each pin individually using the Bit Band feature */
    /* Turn on the Red LED */
    /* Turn on the Blue LED */
    /* Turn on the Green LED */
    PF1_PF2_PF3 = 0x0E;
    Delay_MS(D);
}
#endif
#ifdef SYSTICK
void LED_rolling_systick(uint32 D,uint8 count){   //count for if pll useed so count with it

    uint8 i=0;

    PF1_PF2_PF3 = 0x02;
    while(i < count)
    {
        SYSTICK_enable(D);
        i++;
    }
    i=0;
    PF1_PF2_PF3 = 0x04;
    while(i < count)
    {
        SYSTICK_enable(D);
        i++;
    }
    i=0;
    PF1_PF2_PF3 = 0x08;
    while(i < count)
    {
        SYSTICK_enable(D);
        i++;
    }
    PF1_PF2_PF3 = 0x08;
    while(i < count)
    {
        SYSTICK_enable(D);
        i++;
    }
    PF1_PF2_PF3 = 0x0A;
    while(i < count)
    {
        SYSTICK_enable(D);
        i++;
    }
    PF1_PF2_PF3 = 0x0C;
    while(i < count)
    {
        SYSTICK_enable(D);
        i++;
    }
    PF1_PF2_PF3 = 0x0E;
    while(i < count)
    {
        SYSTICK_enable(D);
        i++;
    }
}
#endif

