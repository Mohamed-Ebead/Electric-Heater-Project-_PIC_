
/*
 * Author: Mohamed  Ebead
 *
 * Created on July , 2020 .
 */

#ifndef I2C_INTERFACE_H
#define	I2C_INTERFACE_H


 
void I2C_Init  (void) ;
void I2C_Hold  (void) ;
void I2C_Start  (void) ;
void I2C_RepeatedStart (void) ;
void I2C_ByteWrite (u8 u8_Data ) ;
u8   I2C_ByteRead  (u8 ack) ;
void I2C_Stop   (void) ;




#endif	/* I2C_INTERFACE_H */

