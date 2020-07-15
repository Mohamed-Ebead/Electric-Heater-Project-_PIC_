
/*
 * Author: Mohamed  Ebead
 *
 * Created on July , 2020 .
 */

#ifndef DIO_GEG_H
#define	DIO_GEG_H

/* Group A Registers */
#define PORTA_Register  (*((volatile u8*)0x05))
#define TRISA_Register  (*((volatile u8*)0x85))

/* Group B Registers */
#define PORTB_Register  (*((volatile u8*)0x06))
#define TRISB_Register  (*((volatile u8*)0x86))

/* Group C Registers */
#define PORTC_Register  (*((volatile u8*)0x07))
#define TRISC_Register  (*((volatile u8*)0x87))

/* Group D Registers */
#define PORTD_Register  (*((volatile u8*)0x08))
#define TRISD_Register  (*((volatile u8*)0x88))




#endif	/* DIO_GEG_H */

