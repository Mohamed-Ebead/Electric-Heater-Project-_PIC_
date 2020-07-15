/*
 * File:   Push_Buttons_Prog.c
 * Author: Mohamed  Ebead
 *
 * Created on July , 2020 .
 */

// shared libraries
#include "Std_Types.h"
#include "Bit_Logic.h"
#include "Configurations.h"

//
#include "Interface.h"

// MCAL
#include "CallBacks.h"
#include "Push_Buttons_int.h"

// HAL 
#include "DIO_Interface.h"
#include "DIO_Reg.h"
#include "EXT_INT_int.h"


// extern used variables 
extern u8 u8_Temp_Buff ;
extern u8 u8_Temp_Set ;
extern u8 ON_OFF_Status ; 
extern u8 Set_Temp_Flag ;
extern u8 TempChange_Status ; 


/*----------------------------------------------------------------------------*/
/*******************************************************************************
 * @fn          : Push_Buttons_Init                                            *
 * @breif       : this function initializes RB0 as an external interrupt input *
 *                for ( ON/OFF button )  , RB4 , RB5 as port change interrupt  *
 *                ( UP button ) and ( DOWN button) respectively .              *
 *                and set their callback functions to their interrupt handlers * 
 * @param[in]   : void                                                         *
 * @return      : void                                                         *
 * @note        :                                                              *
 ******************************************************************************/
void Push_Buttons_Init (void) 
{
    DIO_SetPinDirection ( PORTB_DIO , ON_OFF_BUTTON , INPUT ) ; // set RB0 as input pin for ON/OFF button
    DIO_SetPinDirection ( PORTB_DIO , up_BUTTON , INPUT ) ;     // set RB4 as input pin for UP     button
    DIO_SetPinDirection ( PORTB_DIO , DOWN_BUTTON , INPUT ) ;   // set RB5 as input pin for Down   button
    
    PushButtons_SetCallBacks () ;
    EXT_INT_Init()  ;
}

/*----------------------------------------------------------------------------*/
/*******************************************************************************
 * @fn          : PushButtons_SetCallBacks                                     *
 * @breif       : this function sends the address of the functions to be called* 
 *                to be assigned to the function pointer which will be         *
 *                called from the ISR when its flag is set                     *
 * @param[in]   : void                                                         *
 * @return      : void                                                         *
 * @note        :                                                              *
 ******************************************************************************/
void PushButtons_SetCallBacks (void) 
{
    RB0_SetCallBack     (&RB0_Handler) ;
    RB4_SetCallBack     (&RB4_Handler) ;
    RB5_SetCallBack     (&RB5_Handler) ;
}

/*----------------------------------------------------------------------------*/
/*******************************************************************************
 * @fn          : RB0_Handler                                                  *
 * @breif       : this is the interrupt handler for RB0 interrupt              *
 *                if RB0 is pressed while operating mode , then go sleep       *
 *                otherwise , operating mode is activated  .                   *
 * @param[in]   : void                                                         *
 * @return      : void                                                         *
 * @note        :                                                              *
 ******************************************************************************/

void RB0_Handler (void)
{
    if ( ON_OFF_Status == ON_STATE )
    {
        Sleep_Mode();
    }
    else
    {
       Operating_Mode();
    }
}

/*----------------------------------------------------------------------------*/
/*******************************************************************************
 * @fn          : RB4_Handler                                                  *
 * @breif       : this is the interrupt handler for RB4 interrupt ( UP button )*
 * @param[in]   : void                                                         *
 * @return      : void                                                         *
 * @note        :                                                              *
 ******************************************************************************/
void RB4_Handler (void)
{
   
    if (Set_Temp_Flag == _RESET)
    {
        Set_Temp_Flag = _SET ;
    }
    else 
    {
        if (ON_OFF_Status == ON_STATE)
        {
            if ( u8_Temp_Buff <75 )
            {  
                u8_Temp_Buff += 5 ;
                TempChange_Status = _SET ; 
            }
            else 
            {
                // temp cannot be more than 75 
            }
        }
        else
        {
                // off state 
        }
                
    }
           
}

/*----------------------------------------------------------------------------*/
/*******************************************************************************
 * @fn          : RB4_Handler                                                  *
 * @breif       : this is the interrupt handler for RB5 interrupt (DOWN button)*
 * @param[in]   : void                                                         *
 * @return      : void                                                         *
 * @note        :                                                              *
 ******************************************************************************/
void RB5_Handler (void)
{
    if (Set_Temp_Flag == _RESET)
    {
        Set_Temp_Flag = _SET ;
    }
    else 
    {
        if (ON_OFF_Status == ON_STATE)
        {
            if (u8_Temp_Buff > 35 )
            {
                u8_Temp_Buff -= 5 ;
                TempChange_Status = _SET ; 
            }
            else 
            {
                // temp cannot be less than 35 
            }
        }
        else
        {
                    // off state 
        }
    }
    
}

/******************************************************************************/
