/*
 * File:   I2C_Prog.c
 * Author: Mohamed  Ebead
 *
 * Created on July , 2020 .
 */

// shared libraries
#include "Std_Types.h"
#include "Bit_Logic.h"
#include "Configurations.h"

//HAL
#include "DIO_Interface.h"
#include "I2C_Register.h"


/*----------------------------------------------------------------------------*/
/*******************************************************************************
 * @fn          : I2C_Init                                                     *
 * @breif       : this function Initializes the I2C Protocol                   *
 * @param[in]   : void                                                         *
 * @return      : void                                                         *
 * @note        :                                                              *
 ******************************************************************************/
void I2C_Init  (void) 
{
    
    SSPADD_REGISTER = (_XTAL_FREQ_EEPROM/(4*I2C_SPEED)) - 1;

    SSPCON1_REGISTER = 0b00101000 ;
    SSPSTAT_REGISTER = 0x00 ;
    
    DIO_SetPinDirection(PORTC_DIO , SCL_BIT , INPUT) ;
    DIO_SetPinDirection(PORTC_DIO , SDA_BIT , INPUT) ;
    
}

/*----------------------------------------------------------------------------*/
/*******************************************************************************
 * @fn          : I2C_Hold                                                     *
 * @breif       : this function Holds the execution of the device until the    *
 *                current operation is completed  .                            *
 * @param[in]   : void                                                         *
 * @return      : void                                                         *
 * @note        :                                                              *
 ******************************************************************************/
void I2C_Hold  (void) 
{
 
    while ( (SSPSTAT_REGISTER & 0x04) || (SSPCON2_REGISTER & 0x1F)) ; 
}

/*----------------------------------------------------------------------------*/
/*******************************************************************************
 * @fn          : I2C_Start                                                    *
 * @breif       : this function sends a start bit to the bus  .                *
 * @param[in]   : void                                                         *
 * @return      : void                                                         *
 * @note        :                                                              *
 ******************************************************************************/
void I2C_Start  (void) 
{
     I2C_Hold() ;
    SET_BIT (SSPCON2_REGISTER , _SEN_BIT ) ;    // set SEN bit 
    
}

/*----------------------------------------------------------------------------*/
/*******************************************************************************
 * @fn          : I2C_RepeatedStart                                            *
 * @breif       : this function sends a Repeated start bit to the bus  .       *
 * @param[in]   : void                                                         *
 * @return      : void                                                         *
 * @note        :                                                              *
 ******************************************************************************/
void I2C_RepeatedStart (void)
{
    I2C_Hold() ;
    SET_BIT(SSPCON2_REGISTER , _RSEN_BIT ) ;  // set the repeated start bit 
}

/*----------------------------------------------------------------------------*/
/*******************************************************************************
 * @fn          : I2C_Stop                                                     *
 * @breif       : this function sends a stop condition bit  .                  *
 * @param[in]   : void                                                         *
 * @return      : void                                                         *
 * @note        :                                                              *
 ******************************************************************************/
void I2C_Stop   (void) 
{
   I2C_Hold() ;
   SET_BIT (SSPCON2_REGISTER , _PEN_BIT ) ;   // set PEN bit 
    
    
}

/*----------------------------------------------------------------------------*/
/*******************************************************************************
 * @fn          : I2C_ByteWrite                                                *
 * @breif       : this fun.sends a Byte of data from the master to the slave . *
 * @param[in]   : u8_Data : the Byte of data to be send.                       *
 * @return      : void                                                         *
 * @note        :                                                              *
 ******************************************************************************/
void I2C_ByteWrite (u8 u8_Data ) 
{
    I2C_Hold();
    SSPBUF_REGISTER = u8_Data ;
}

/*----------------------------------------------------------------------------*/
/*******************************************************************************
 * @fn          : I2C_ByteRead                                                 *
 * @breif       : this fun. reads the Byte of data that is currently on the bus*
 * @param[in]   : u8 ack : the acknowledge bit                                 *
 * @return      : u8_DataRead : the data BYTE  read from the I2C bus .         *
 * @note        :                                                              *
 ******************************************************************************/
u8 I2C_ByteRead  (u8 ack) 
{
    u8 u8_DataRead ; 
    I2C_Hold() ;
    SET_BIT(SSPCON2_REGISTER , _RCEN_BIT) ; // set RCEN bit recieve enable bit
    
    I2C_Hold() ;
    u8_DataRead = SSPBUF_REGISTER ;
    
    I2C_Hold() ;
    
    if (ack)
    {
        SET_BIT(SSPCON2_REGISTER , _ACKDT_BIT);  // ACKDT bit 
    }
    else
    {
        CLR_BIT(SSPCON2_REGISTER , _ACKDT_BIT);

    }
    
    SET_BIT(SSPCON2_REGISTER,_ACKEN_BIT ) ; // ack sequence enable bit 
    
    return u8_DataRead ;
}
/******************************************************************************/