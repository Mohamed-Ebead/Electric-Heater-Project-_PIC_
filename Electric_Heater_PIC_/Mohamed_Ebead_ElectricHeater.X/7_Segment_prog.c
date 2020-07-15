/*
 * File:   7_Segment_prog.c
 * Author: Mohamed  Ebead
 *
 * Created on July , 2020 .
 */


// shared libraries 
#include <xc.h>
#include "Std_Types.h"
#include "Configurations.h"

// MCAL
#include "_7_segment_private.h"

// HAL
#include "DIO_Interface.h"



/*----------------------------------------------------------------------------*/
/*******************************************************************************
 * @fn          : Seven_Segments_Init                                          *
 * @breif       : this function Initializes both seven segments                *
 * @param[in]   : void                                                         *
 * @return      : void                                                         *
 * @note        :                                                              *
 ******************************************************************************/
void Seven_Segments_Init (void) 
{
    DIO_SetPinDirection(PORTA_DIO , L_CTRL , OUTPUT) ; // control signal for left 7-segment
    DIO_SetPinDirection(PORTA_DIO , R_CTRL , OUTPUT) ; // control signal for right 7-segment
    
    DIO_SetPortDirection(PORTD_DIO , 0x00) ; // SET PORTD output for 7-segment 
    
    // Initialization 
    DIO_SetPinValue(PORTA_DIO , L_CTRL , LOW) ; 
    DIO_SetPinValue(PORTA_DIO , R_CTRL , LOW) ; 
    
}

/*----------------------------------------------------------------------------*/
/*******************************************************************************
 * @fn          : vid_7_Segment_DeInit                                         *
 * @breif       : this function DeInitializes both seven segments              *
 * @param[in]   : void                                                         *
 * @return      : void                                                         *
 * @note        :                                                              *
 ******************************************************************************/
void Seven_Segments_DeInit (void) 
{
    DIO_SetPortValue(PORTD_DIO , 0x00 ) ; 

    DIO_SetPinValue(PORTA_DIO , L_CTRL , LOW) ; 
    DIO_SetPinValue(PORTA_DIO , R_CTRL , LOW) ;
}
/*----------------------------------------------------------------------------*/
/*******************************************************************************
 * @fn          : Left_7_Segment_DisplayDigit                                 *
 * @breif       : this function Displays one digit on the left 7-segment       *
 * @param[in]   : u8_Digit to be displayed                                     *
 * @return      : void                                                         *
 * @note        : u8_Digit must be <= 9                                                              *
 ******************************************************************************/
void Left_7_Segment_DisplayDigit (u8 u8_LDigit ) 
{
    if (u8_LDigit <= 9 )
    {
    DIO_SetPinValue(PORTA_DIO , R_CTRL , LOW) ;   // disable right 7-segment
    DIO_SetPinValue(PORTA_DIO , L_CTRL , HIGH) ;  // enable left 7-segment
    
    DIO_SetPortValue(PORTD_DIO,u8_Left_7Segment[u8_LDigit]) ;
    }
    else
    {
        // more than one digit  can not be displayed on one 7-segment
    }
    
}

/*----------------------------------------------------------------------------*/
/*******************************************************************************
 * @fn          : Right_7_Segment_DisplayDigit                                 *
 * @breif       : this function Displays one digit on the Right 7-segment      *
 * @param[in]   : u8_Digit to be displayed                                     *
 * @return      : void                                                         *
 * @note        : u8_Digit must be <= 9                                                               *
 ******************************************************************************/
void Right_7_Segment_DisplayDigit (u8 u8_RDigit ) 
{
    if (u8_RDigit <= 9 )
    {
        DIO_SetPinValue(PORTA_DIO , L_CTRL , LOW) ;  // disable left 7-segment
        DIO_SetPinValue(PORTA_DIO , R_CTRL , HIGH) ; // enable right 7-segment
        DIO_SetPortValue(PORTD_DIO,u8_Right_7Segment[u8_RDigit]) ;
    }
    else
    {
        // more than one digit  can not be displayed on one 7-segment
    }
    
}

/*----------------------------------------------------------------------------*/
/*******************************************************************************
 * @fn          : Seven_Segments_Display_2Digits                               *
 * @breif       : this function Displays two digits on the 2 seven- segments   *
 * @param[in]   : u8_Num  to be displayed                                      *
 * @return      : void                                                         *
 * @note        : u8_Num must be <= 99                                         *
 ******************************************************************************/
void Seven_Segments_Display_2Digits (u8 u8_Num ) 
{
    if (u8_Num <= 99 )
    {
        u8 Ones = u8_Num % 10 ;
        u8 Tens = u8_Num / 10 ;
    
        Right_7_Segment_DisplayDigit (Ones) ;
        __delay_ms(1);        // delay for stability 
        Left_7_Segment_DisplayDigit  (Tens) ;
        __delay_ms(1);        // delay for stability 


        DIO_SetPinValue(PORTA_DIO , L_CTRL , LOW) ; 
    }
    else
    {
        // number greater than 99 can not be displayed on 2 seven-segments 
    }
    
}
/******************************************************************************/
        