/*
 * File:   EXT_INT_Prog.c
 * Author: Mohamed  Ebead
 *
 * Created on July , 2020 .
 */

//shared libraries 
#include "Std_Types.h"
#include "Bit_Logic.h"


// MCAL


// HAL
#include "INT_Reg.h"


/*----------------------------------------------------------------------------*/
/*******************************************************************************
 * @fn          : EXT_INT_Init                                                 *
 * @breif       : this function Initializes external interrupt                 *
 *                for RB0 and RB PORT change interrupt  .                      *
 * @param[in]   : void                                                         *
 * @return      : void                                                         *
 * @note        :                                                              *
 ******************************************************************************/
void EXT_INT_Init (void) 
{
    
    CLR_BIT (OPTION_REGISTER , OPTION_RBPU ) ;       // connect PORTB to pull up resistors
      
    CLR_BIT (OPTION_REGISTER , OPTION_INTEDG ) ;       // Falling edge 
    SET_BIT (INTCON_REGISTER , INTCON_INTE ) ;         // RB0 int enable 
    SET_BIT (INTCON_REGISTER , INTCON_RBIE ) ;         // RB PORT change interrupt enable 
    SET_BIT (INTCON_REGISTER , INTCON_GIE ) ;          // global int enable 
}
/******************************************************************************/

