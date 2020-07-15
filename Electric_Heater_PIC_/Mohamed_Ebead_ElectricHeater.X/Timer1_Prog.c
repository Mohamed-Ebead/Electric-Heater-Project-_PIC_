/*
 * File:   Timer1_Prog.c
 * Author: Mohamed  Ebead
 *
 * Created on July , 2020 .
 */

// shared libraries 
#include "Std_Types.h"
#include "Bit_Logic.h"


// HAL
#include "Timer1_Reg.h"
#include "DIO_Reg.h"
#include "DIO_Interface.h"

#include "CallBacks.h"

/*----------------------------------------------------------------------------*/
/*******************************************************************************
 * @fn          : TempSensor_Init                                              *
 * @breif       : this function initializes the timer 1 in compare mode with   *
 *                prescaler 1:8 so freq = 8MHZ/8 = 1MHZ , time of tick = 1 us ,* 
 *                and a preload value = 1000 , so that tick time = 1 ms .      *
 * @param[in]   : void                                                         *
 * @return      : void                                                         *
 * @note        :                                                              *
 ******************************************************************************/
void Timer1_Init_Comp (void) 
{
    // reset timer register 
    TMR1L_REGISTER = 0 ;
    TMR1H_REGISTER = 0 ; 
    
    /* timer1 initialization : 
     *  1 : 8 prescaler , so 8MHZ/8 = 1MHZ , time of tick = 1 us
     * oscillator is shut off , do not synch external clock
     * Internal clock 
     * enable timer 1 
     */
    T1CON_REGISTER = 0b00110001 ;
    
    
    /* ccp initialization 
     * compare mode , trigger special event 
     */
    CCP1CON_REGISTER = 0b00001011 ;
    
    // preload value = 1000 , so that tick time = 1 ms
    CCPR1_REGISTER = 1000 ; 
    
    // CCP1 interrupt enable 
    SET_BIT(PIE1_REGISTER , CCP1IE_BIT ) ;
    
    // PERIPHERAL INTERRUPT ENABLE 
    SET_BIT(INTCON_REGISTE ,PEIE_BIT ) ;
    
    // GLOBAL INTERRUPT ENABLE 
    SET_BIT(INTCON_REGISTE ,GIE_BIT ) ;
    
    Timer1_SetCallBack  (&Temp_ControlWaterTemp) ;
}

/******************************************************************************/
