/*
 * File:   Program.c
 * Author: Mohamed  Ebead
 *
 * Created on July , 2020 
 */

//shared libraries 
#include <xc.h>
#include "Std_Types.h"
#include "Bit_Logic.h"
#include "Configurations.h"


//APP
#include "Interface.h"


// MCAL
#include "Actuators_int.h"
#include "_7_Segment_int.h"
#include "Configurations.h"
#include "EEPROM_int.h"

// HAL
#include "INT_Reg.h"
#include "Timer1_Reg.h"




// extern used variables 
extern u8 ON_OFF_Status ; 
extern u8 u8_Temp_Set  ;
extern u8 u8_Water_Temp ; 
extern u8 Set_Temp_Flag ;
extern u8 TempChange_Status ; 
extern u8 u8_Temp_Buff ;


/*----------------------------------------------------------------------------*/
/*******************************************************************************
 * @fn          : u8_System_WakeUp                                             *
 * @breif       : this function enables checks the ON/OFF status               *
 * @param[in]   : void                                                         *
 * @return      : return 1 if ON_STATE and 0 otherwise                         *
 * @note        :                                                              *
 ******************************************************************************/
 
u8 u8_System_WakeUp (void)
{
    if (ON_OFF_Status == ON_STATE)
    {
        return 1 ;
    }
    return 0 ;
}
/*----------------------------------------------------------------------------*/
/*******************************************************************************
 * @fn          : SystemVars_Init                                              *
 * @breif       : this fun.  Initializes the system variables once powered up  *
 * @param[in]   : void                                                         *
 * @return      : void                                                         *
 * @note        :                                                              *
 ******************************************************************************/
void SystemVars_Init (void) 
{
    if ( (EEPROM_ReadFromEEPROM() <= 75 ) && (EEPROM_ReadFromEEPROM() >= 35 ) )
    {
        // do not change value 
    }
    else
    {
        EEPROM_WriteToEEPROM(TEMP_INIT) ;
    }
    
    u8_Temp_Set = EEPROM_ReadFromEEPROM() ;
    u8_Temp_Buff = u8_Temp_Set;
    ON_OFF_Status = OFF_STATE ; 
    Set_Temp_Flag = _RESET ;
    TempChange_Status = _RESET ; 
}

/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/*******************************************************************************
 * @fn          : Operating_Mode                                               *
 * @breif       : Operating mode : 7-segments display current water temp       *
 *                  ,  enables RB PORT change interrupts and timer interrupt   *
 *                  ,  checks the temp Set Mode Flag                           *
 * @param[in]   : void                                                         *
 * @return      : void                                                         *
 * @note        :                                                              *
 ******************************************************************************/
void Operating_Mode (void) 
{     
    ON_OFF_Status = ON_STATE ; 
    
    Seven_Segments_Display_2Digits(u8_Water_Temp) ;
   SET_BIT (INTCON_REGISTER , INTCON_RBIE ) ;         // RB PORT change interrupt enable 
   SET_BIT(PIE1_REGISTER , CCP1IE_BIT ) ;             // Timer interrupt enable 
   
    if (Set_Temp_Flag == _SET)
    {
         SetTemp_Mode() ;
    }
    else
    {
            // Set_Temp_Flag == _RESET
    }
   
}

/*----------------------------------------------------------------------------*/
/*******************************************************************************
 * @fn          : Sleep_Mode                                                   *
 * @breif       : Sleep Mode : 7-segments display is turned off                *
 *                  , Turns off the cooler and the heating element             *
 *                  ,  disables RB PORT change interrupts and timer interrupt  *
 * @param[in]   : void                                                         *
 * @return      : void                                                         *
 * @note        :                                                              *
 ******************************************************************************/
void Sleep_Mode (void) 
{
    ON_OFF_Status = OFF_STATE ;
    Seven_Segments_DeInit () ;
    Heater_TurnOff() ;
    Cooler_TurnOff() ; 
    CLR_BIT (INTCON_REGISTER , INTCON_RBIE ) ;        // RB PORT change interrupt disable 
    CLR_BIT(PIE1_REGISTER , CCP1IE_BIT ) ;            // Timer interrupt disable 

}

/*----------------------------------------------------------------------------*/
/*******************************************************************************
 * @fn          : SetTemp_Mode                                                 *
 * @breif       : Set Temperature Mode : if UP or DOWN button is pressed while *
 *                    operating mode is active then , this function will be    *
 *                    called to set the desired water temperature to be        *
 *                    7-segments blinks with the temp. set by user .           *
 * @param[in]   : void                                                         *
 * @return      : void                                                         *
 * @note        : this function lasts only 5 seconds from last UP/Down press   *
 *                to get these 5 seconds blinking then we have to loop 5 turns *
 *                each turn take 1 second (500 ms on and 500 ms off)           *
 *                as 7-segments takes 2 ms to display the 2-digits , then we   *
 *                can loop 250 turn to get the 500 ms on .                     *  
 *                if any of UP/DOWN button is pressed , then start the 5 loops *
 *                from the beginning .                                         *
 ******************************************************************************/
void  SetTemp_Mode (void) 
{
    u8 count = 0 ;
    u8 stability = 0 ; 

        for (count=0;count<5;count++)
        {
            for (stability = 0 ;stability <250 ; stability ++ )
            { 
                Seven_Segments_Display_2Digits(u8_Temp_Buff) ;
            }

            Seven_Segments_DeInit() ;
            __delay_ms(500) ;
            
            if (TempChange_Status == _SET)
            {
                count = 0 ; 
                TempChange_Status = _RESET ; 
            }
        }
        
        Set_Temp_Flag = _RESET  ; 
        u8_Temp_Set = u8_Temp_Buff ;

        EEPROM_WriteToEEPROM(u8_Temp_Set) ;
    
}

/*----------------------------------------------------------------------------*/

/*------------------------------- End Of The File ----------------------------*/

