/* 
 *
 * Author: Mohamed Ebead
 *
 * Created on July , 2020 .
 * 
 */

#ifndef TIMER1_REG_H
#define	TIMER1_REG_H

#define TMR1L_REGISTER    (*((volatile u8*)0x0E))
#define TMR1H_REGISTER    (*((volatile u8*)0x0F))

#define T1CON_REGISTER    (*((volatile u8*)0x10))
#define T1CON_T1OSCEN   3
#define T1CON_T1SYNC    2
#define T1CON_TMR1CS    1
#define T1CON_TMR1ON    0


#define CCP1CON_REGISTER  (*((volatile u8*)0x17))

#define CCPR1L_REGISTER    (*((volatile u8*)0x15))
#define CCPR1H_REGISTER    (*((volatile u8*)0x16))

#define CCPR1_REGISTER    (*((volatile u16*)0x15))


#define PIE1_REGISTER    (*((volatile u8*)0x8C))
#define CCP1IE_BIT       2

#define PIR1_REGISTER    (*((volatile u8*)0x0C))
#define CCP1IF_BIT       2

#define INTCON_REGISTE   (*((volatile u8*)0x0B))
#define GIE_BIT          7
#define PEIE_BIT         6



#endif	/* TIMER1_REG_H */

