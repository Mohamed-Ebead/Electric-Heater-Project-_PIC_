/*
 * Author: Mohamed  Ebead
 *
 * Created on July , 2020 .
 */


#ifndef ADC_REG_H
#define	ADC_REG_H


#define ADCCON0_REGISTER  (*((volatile u8*)0x1F))
#define ADCCON1_REGISTER  (*((volatile u8*)0x9F))


#define ADRESH_REGISTER   (*((volatile u8*)0x1E))
#define ADRESL_REGISTER   (*((volatile u8*)0x9E))




#endif	/* ADC_REG_H */

