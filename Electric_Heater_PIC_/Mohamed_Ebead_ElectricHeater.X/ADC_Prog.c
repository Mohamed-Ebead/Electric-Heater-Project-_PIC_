
/*
 * File:   ADC_Prog.c
 * Author: Mohamed  Ebead
 *
 * Created on July , 2020 
 */


// shared libraries 
//#include <xc.h>
#include "Std_Types.h"
#include "Bit_Logic.h"
#include "Configurations.h"


// HAL
#include "ADC_Reg.h"



/*----------------------------------------------------------------------------*/
/*******************************************************************************
 * @fn          : ADC_Init                                                     *
 * @breif       : this function Initializes ADC peripheral                     *
 * @param[in]   : void                                                         *
 * @return      : void                                                         *
 * @note        :                                                              *
 ******************************************************************************/
void ADC_Init (void) 
{
    /* Turn ADC ON 
     * Select AN0 Channel 
     * ADC clock = Fosc/8 
     */
    ADCCON0_REGISTER = 0x41 ; 
    
    /* All 6 channels are analog 
     * Result is right justified 
     */
    ADCCON1_REGISTER = 0x80 ; 
    
}

/*----------------------------------------------------------------------------*/
/*******************************************************************************
 * @fn          : u16_ADC_Read                                                 *
 * @breif       : this function Reads the Analog value from tha ADC Channel    *  
 * @param[in]   : u8_Channel : the channel to witch the sensor is connected    *                                *
 * @return      : u16 the analog value corresponding to the desired Channel    *                                                      *
 * @note        :                                                              *
 ******************************************************************************/
u16   u16_ADC_ReadChannel (u8 u8_Channel) 
{
    // u8_Channel must be <= 5
    if ((u8_Channel <= 0) || (u8_Channel >= 5) )
    {
       return 0 ;  
    }
    
    ADCCON0_REGISTER &= 0b11000101 ;       // clear channel selection bits 
    ADCCON0_REGISTER |= (u8_Channel <<3) ; // select the required channel 
    
    
    SET_BIT(ADCCON0_REGISTER , 2 ) ;  // set GO/DONe bit to start the conversion 
    
    while ( GET_BIT(ADCCON0_REGISTER , 2 )) ; // polling GO_DONE bit 
    
    return (u16)( (ADRESH_REGISTER << 8) + ADRESL_REGISTER ) ;
   
}

/*----------------------------------------------------------------------------*/
/******************************************************************************/