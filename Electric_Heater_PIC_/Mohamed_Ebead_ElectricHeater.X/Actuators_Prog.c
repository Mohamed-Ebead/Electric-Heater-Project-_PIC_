/*
 * File:   Actuators_Prog.c
 * Author: Mohamed  Ebead
 *
 * Created on July , 2020 
 */


// shared libraries
#include "Std_Types.h"
#include "Bit_Logic.h"
#include "Configurations.h"


// MCAL


// HAL 
#include "DIO_Interface.h"
#include "DIO_Reg.h"

extern u8 Cooler_Status ; 

/******************************* Cooler Module ********************************/
/*----------------------------------------------------------------------------*/
/*******************************************************************************
 * @fn          : Cooler_Init                                                  *
 * @breif       : this function Initializes the cooler ( the fan )             *
 * @param[in]   : void                                                         *
 * @return      : void                                                         *
 * @note        :                                                              *
 ******************************************************************************/

void Cooler_Init (void) 
{
    DIO_SetPinDirection ( PORTC_DIO , FAN , OUTPUT ) ;

    DIO_SetPinValue     ( PORTC_DIO , FAN , LOW ) ;
    
    Cooler_Status  = _RESET ; 

}

/*----------------------------------------------------------------------------*/
/*******************************************************************************
 * @fn          : Cooler_TurnOn                                                *
 * @breif       : this function Turns on the cooler ( the fan )                *
 * @param[in]   : void                                                         *
 * @return      : void                                                         *
 * @note        : Heating element led is on                                                    *
 ******************************************************************************/
void Cooler_TurnOn  (void) 
{
    DIO_SetPinValue ( PORTC_DIO , FAN , HIGH ) ;
    DIO_SetPinValue  (PORTB_DIO , HEATER_LED , HIGH) ;  // turn on heating element led 
     Cooler_Status  = _SET ; 

}

/*----------------------------------------------------------------------------*/
/*******************************************************************************
 * @fn          : Cooler_TurnOff                                               *
 * @breif       : this function Turns Off  the cooler ( the fan )              *
 * @param[in]   : void                                                         *
 * @return      : void                                                         *
 * @note        :                                                              *
 ******************************************************************************/
void Cooler_TurnOff (void) 
{
    DIO_SetPinValue  ( PORTC_DIO , FAN , LOW ) ;
    DIO_SetPinValue  (PORTB_DIO , HEATER_LED , LOW) ; 
    Cooler_Status  = _RESET ; 
}

/*----------------------------------------------------------------------------*/
/******************************************************************************/

/******************************* Heater Module ********************************/
/*----------------------------------------------------------------------------*/
/*******************************************************************************
 * @fn          : Heater_Init                                                  *
 * @breif       : this function Initializes the Heating element                *
 * @param[in]   : void                                                         *
 * @return      : void                                                         *
 * @note        :                                                              *
 ******************************************************************************/
void Heater_Init (void) 
{
    DIO_SetPinDirection ( PORTC_DIO , HEATER , OUTPUT ) ;
    DIO_SetPinDirection ( PORTB_DIO , HEATER_LED , OUTPUT ) ;
    
    DIO_SetPinValue     ( PORTC_DIO , HEATER , LOW ) ;
    DIO_SetPinValue     ( PORTB_DIO , HEATER_LED , LOW ) ;

}

/*----------------------------------------------------------------------------*/
/*******************************************************************************
 * @fn          : Heater_TurnOn                                                *
 * @breif       : this function Turns on the Heating elemnt                    *
 * @param[in]   : void                                                         *
 * @return      : void                                                         *
 * @note        : this function is entered every 1 second (interrupt time is   *
 *                neglected) because Temp_ControlWaterTemp() function takes    *
 *                action every 1 second as it measures the temperature every   *
 *                100 ms and for every 10 measurements (10*100=1000 ms = 1sec) *
 *                it takes an action, so if the Heating element  is turned on  *
 *                , the led (B2)  is toggled every 1 second ( blinking ) .     *                                                          *
 ******************************************************************************/
void Heater_TurnOn  (void) 
{
    DIO_SetPinValue ( PORTC_DIO , HEATER , HIGH ) ;
    TOG_BIT (PORTB_Register , HEATER_LED) ;   
}

/*----------------------------------------------------------------------------*/
/*******************************************************************************
 * @fn          : Heater_TurnOff                                               *
 * @breif       : this function Turns Off  the Heating element                 *
 * @param[in]   : void                                                         *
 * @return      : void                                                         *
 * @note        :                                                              *
 ******************************************************************************/
void Heater_TurnOff (void) 
{
    DIO_SetPinValue     ( PORTC_DIO , HEATER , LOW ) ;
    DIO_SetPinValue     (PORTB_DIO , HEATER_LED , LOW) ; 
}

/*----------------------------------------------------------------------------*/
/******************************************************************************/
