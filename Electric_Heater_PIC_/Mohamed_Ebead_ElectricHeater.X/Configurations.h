/*
 * Author: Mohamed  Ebead
 *
 * Created on July , 2020 .
 */



#ifndef CONFIGURATIONS_H
#define	CONFIGURATIONS_H


#define _XTAL_FREQ      8000000


// seven segment 
#define L_CTRL          PIN4
#define R_CTRL          PIN5

//sensors 
#define LM35            PIN2

//actuators 
#define FAN             PIN2 
#define HEATER          PIN5
#define HEATER_LED      PIN1

#define ON_OFF_BUTTON   PIN0
#define up_BUTTON       PIN4
#define DOWN_BUTTON     PIN5


// temp initial value 
#define TEMP_INIT       60


#define OFF_STATE       0
#define ON_STATE        1

#define _RESET          0 
#define _SET            1 


 // I2C and EEPROM 
#define _XTAL_FREQ_EEPROM          20000000
#define I2C_SPEED                  100000
#define EEPROM_ADDRESS_Write       (u8)0xA0   // address as picsimlab ,last bit = 0 to write 
#define EEPROM_ADDRESS_READ        (u8)0xA1   // address as picsimlab ,last bit = 0 to write 

#define EEPROM_BYTE_ADDRESS        (u8)0x00 





#endif	/* CONFIGURATIONS_H */

