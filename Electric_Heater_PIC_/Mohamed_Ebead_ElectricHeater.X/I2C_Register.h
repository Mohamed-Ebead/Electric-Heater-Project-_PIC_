/* 
 *
 * Author: Mohamed Ebead
 *
 * Created on July , 2020 .
 */

#ifndef I2C_REGISTER_H
#define	I2C_REGISTER_H



#define SSPADD_REGISTER     (*((volatile u8*)0x93))
#define SSPSTAT_REGISTER    (*((volatile u8*)0x94))
#define SSPCON1_REGISTER    (*((volatile u8*)0x14))
#define SSPCON2_REGISTER    (*((volatile u8*)0x91))
#define _SEN_BIT            0
#define _RSEN_BIT           1
#define _PEN_BIT            2
#define _RCEN_BIT           3
#define _ACKEN_BIT          4
#define _ACKDT_BIT          5





#define SSPBUF_REGISTER     (*((volatile u8*)0x13))

#define PIR1_REGISTER       (*((volatile u8*)0x0C))
#define PIR1_SSPIF          3 

#define TRISC_Register      (*((volatile u8*)0x87))

#define SCL_BIT  3
#define SDA_BIT  4





#endif	/* I2C_REGISTER_H */

