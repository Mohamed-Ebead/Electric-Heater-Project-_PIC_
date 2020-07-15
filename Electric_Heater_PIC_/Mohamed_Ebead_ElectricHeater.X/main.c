/*
 * File:   main.c
 * Author: Mohamed  Ebead
 *
 * Created on July , 2020.
 */

// shared libraries 
#include <xc.h>
#include "MCU_Config.h"
#include "Configurations.h"
#include "Std_Types.h"
#include "Bit_Logic.h"
#include "System_Vars.h"

// APP
#include "Interface.h"

//MCAL
#include "_7_Segment_int.h"
#include "Push_Buttons_int.h"
#include "EEPROM_int.h"
#include "Temp_Sensor_int.h"
#include "Actuators_int.h"





int main(void) {
    
   
    Heater_Init() ;          // Initialize The Heating element 
    Cooler_Init();           // Initialize the Fan 
    TempSensor_Init () ;     // Initialize LM35 temperature sensor  
    EEPROM_Init () ;         // Initialize 24C04 External EEPROM 
    Push_Buttons_Init() ;    // Initialize ON/OFF , UP , and Down Buttons
    Seven_Segments_Init() ;  // Initialize both  7-Segment s
    
   
    Sleep_Mode();            // start system in sleep mode 
    SystemVars_Init () ;     // Initialize system variables 



    while (1)
    {

      // check ON/OFF Status to set the system mode  
        while (u8_System_WakeUp())
        {
            Operating_Mode() ;
            
        }
        
        // if (ON_OFF_Status == OFF_STATE) , then go Sleep 
        Sleep_Mode();
        __asm__  ("SLEEP") ;  // save Power until system wake up 

        
        
    }
    return 0 ;
}


