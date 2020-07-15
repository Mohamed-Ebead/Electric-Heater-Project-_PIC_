/*
 * File:   Temp_Sensor_Prog.c
 * Author: Mohamed  Ebead
 *
 * Created on July , 2020 .
 */


// shared libraries
#include "Std_Types.h"
#include "Bit_Logic.h"
#include "Configurations.h"


// MCAL
#include "CallBacks.h"
#include "Actuators_int.h"


// HAL 
#include "ADC_int.h"
#include "DIO_Interface.h"
#include "Timer1_int.h"


// extern used variables
extern u8 ON_OFF_Status ; 
extern u8 u8_Temp_Set  ;
extern u8 u8_Water_Temp ; 
extern u16 u16_ADC_Read ; 
extern u16 u16_Voltage ; 
extern u8 u8_Counter  ;
extern u8 u8_arr_Temp[10]  ;
extern u8 u8_Temp_Buff ;
extern u8 Cooler_Status ; 

/*----------------------------------------------------------------------------*/
/*******************************************************************************
 * @fn          : TempSensor_Init                                              *
 * @breif       : this function initializes the lm35 temperature sensor by     *
 *                initializing ADC peripheral and prepare lm35 channel as an   *
 *                input , then initializes timer1 in compare mode to use       *
 *                timer interrupt to call the function witch reads the temp.   *
 *                every 100 ms and take an action based on the average for     *
 *                every 10 readings .(it means , it takes action on cooler and *
 *                heater every 10*100 = 1000 ms == 1second ) .                 *
 * @param[in]   : void                                                         *
 * @return      : void                                                         *
 * @note        :                                                              *
 ******************************************************************************/
void TempSensor_Init (void) 
{
    DIO_SetPinDirection(PORTA_DIO , LM35 , INPUT );
    ADC_Init() ;  
    Timer1_SetCallBack(Temp_ControlWaterTemp) ; 
    Timer1_Init_Comp();

}

/*----------------------------------------------------------------------------*/
/*******************************************************************************
 * @fn          : Temp_ControlWaterTemp                                        *
 * @breif       : this function is called from timer ISR using callback fun. 
 *                every 100 ms to read the analog value from lm35 sensor 
 *                and convert it to corresponding digital value and then take 
 *                an action based on the average for every 10 readings .
 *                if the average temp is greater than or equal temp. set 
 *                by the user by 5 degrees or more , then turn the cooler on
 *                cools the water to reach the set value , else if the average 
 *                temp is less than or equal temp. set by the user by 5 degrees 
 *                or more , then turn the heater on and turn off the cooler .
 *                otherwise , both cooler and heater are turned off .  
 * @param[in]   : void                                                         *
 * @return      : void                                                         *
 * @note        :                                                              *
 ******************************************************************************/
void Temp_ControlWaterTemp (void) 
{
if (ON_OFF_Status == ON_STATE)
{    
    u8 iterator = 0 ;
    u16 u16_Temp_Avg = 0 ; 
    
    u16_ADC_Read = u16_ADC_ReadChannel(LM35);
    u16_Voltage = ((u16_ADC_Read * 5000UL) /1024UL ) ;
    u8_Water_Temp = (u8) (u16_Voltage / 10 ); 
    
    u8_arr_Temp[u8_Counter] = u8_Water_Temp ;
    u8_Counter ++ ; 
    
    if (u8_Counter == 10 )
    {
        u8_Counter = 0 ;
        // get the average of the last 10 measurements
        for ( iterator = 0 ; iterator < 10 ; iterator ++  )
        {
            // add all the elements of the temperature array 
            u16_Temp_Avg = u16_Temp_Avg + u8_arr_Temp[iterator] ;
        }
        // divide the summation by 10 to get the average temp 
        u16_Temp_Avg = (u8) ( u16_Temp_Avg / 10 ) ; 
        
        // control the heater and the cooler based on the average temp
        if ( u16_Temp_Avg >= ( u8_Temp_Set + 5 ) )
        {
            Heater_TurnOff() ;
            Cooler_TurnOn() ;
            return ;
        }
        else if ( u16_Temp_Avg <= ( u8_Temp_Set - 5 ) )
        {
            if (Cooler_Status == _SET)
            {
                Cooler_TurnOff() ;
            }
            Heater_TurnOn() ;
            return ;

        }
        else          // (u8_Water_Temp == u8_Temp_Set)
        {
            Cooler_TurnOff() ;
            Heater_TurnOff() ; 
            return ;

        } 
    }
   else
    {
        // wait until 10th measure 
    }
}
else
{
    // OFF mode 
}
          
}
/******************************************************************************/




