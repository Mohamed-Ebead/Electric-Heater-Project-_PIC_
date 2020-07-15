/*
 * File:   EEPROM_Prog.c
 * Author: Mohamed  Ebead
 *
 * Created on July , 2020 .
 */

// shared libraries
#include "Std_Types.h"
#include "Bit_Logic.h"
#include "Configurations.h"

// MCAL

// HAL
#include "I2C_interface.h"
#include "I2C_Register.h"


/*----------------------------------------------------------------------------*/
/*******************************************************************************
 * @fn          : EEPROM_Init                                                  *
 * @breif       : this function Initializes the EEPROM                         *
 *                by Initializing I2C protocol                                 *                                            
 * @param[in]   : void                                                         *
 * @return      : void                                                         *
 * @note        :                                                              *
 ******************************************************************************/
void EEPROM_Init (void) 
{
    I2C_Init() ;    
    
}

/*----------------------------------------------------------------------------*/
/*******************************************************************************
 * @fn          : EEPROM_WriteToEEPROM                                         *
 * @breif       : this function Writes a u8 value to the EEPROM                *
 *                by Initializing I2C protocol                                 *                                            
 * @param[in]   : u8_Data to be written                                        *
 * @return      : void                                                         *
 * @note        : the address of the EEPROM to witch the fun. writes is        *
 *                fixed to EEPROM_BYTE_ADDRESS (0x00) as the app needs         *
 *                to store one value .                                         *
 ******************************************************************************/
void EEPROM_WriteToEEPROM (u8 u8_Data) 
{
    I2C_Start() ;
    
    I2C_ByteWrite(EEPROM_ADDRESS_Write) ;
    I2C_ByteWrite(EEPROM_BYTE_ADDRESS);
    I2C_ByteWrite(u8_Data);    
    I2C_Stop() ;
}

/*----------------------------------------------------------------------------*/
/*******************************************************************************
 * @fn          : EEPROM_ReadFromEEPROM                                        *
 * @breif       : this function Reads a u8 value From the EEPROM               *
 * @param[in]   : void                                                         *
 * @return      : u8_Data which is read fromm EEPROM                           *
 * @note        : the address of the EEPROM from witch the fun. reads is       *
 *                fixed to EEPROM_BYTE_ADDRESS (0x00) as the app needs         *
 *                to read one value .                                          *                                                           *
 ******************************************************************************/

u8 EEPROM_ReadFromEEPROM (void) 
{
     u8 Data ; 
    
    I2C_Start() ;
    I2C_ByteWrite(EEPROM_ADDRESS_Write);

    I2C_ByteWrite(EEPROM_BYTE_ADDRESS);
    I2C_RepeatedStart();
    
    I2C_ByteWrite(EEPROM_ADDRESS_READ);

    Data = I2C_ByteRead(0) ;
    
    I2C_Stop() ;
    
   return Data ;
}
/******************************************************************************/